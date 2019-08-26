#include "RenderingManager.h"
#include "Application.h"
#include "RenderComponent.h"
#include "EntityScript.h"
#include "PlayerScript.h"

#define VIEW_AS_LIGHT false
#define SHADOW_VIEW_SIZE_X 400
#define SHADOW_VIEW_SIZE_Y 200/16*9
#define SHADOW_VIEW_SIZE_Z 400
#define SHADOW_RES 128*20.f

#define SWITCH_SHADER true
RenderingManager::RenderingManager()
{
	m_worldHeight = 100.f;
	m_worldWidth = 100.f;
	m_speed = 1.f;
}

RenderingManager::~RenderingManager()
{
}

void RenderingManager::Init()
{
	RenderingManagerBase::Init();
	// Shadows
	m_lightDepthFBO.Init((unsigned)(SHADOW_RES), (unsigned)(SHADOW_RES));
	m_lightDepthFBO.Init(SHADOW_RES, SHADOW_RES);
	Post.Init(Application::GetWindowWidth(), Application::GetWindowHeight());
	Post2.Init(Application::GetWindowWidth(), Application::GetWindowHeight());
	Math::InitRNG();
	glGenRenderbuffers(1, &m_PostBO);
	glGenRenderbuffers(1, &m_PostBO2);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	SceneManager* SceneManager = SceneManager::GetInstance();
	Scene* CurrentScene = SceneManager->GetScene();
	Camera* Cam = CurrentScene->GetCamera();

	//Cam->UpdateYawPitchMouse((float)xpos, (float)ypos);
}
void RenderingManager::RenderQueued(Scene* scene)
{
	for (GameObject* go : RenderQueue)
	{
		RenderGameObject(go, scene->GetCameraGameObject()->GetComponent<TransformComponent>()->GetPosition(), false, false);
	}
	RenderQueue.clear();
}
void RenderingManager::SetMouseCallback(GLFWwindow* window)
{
	glfwSetCursorPosCallback(window, mouse_callback);
}

void RenderingManager::Update(double dt)
{
	RenderingManagerBase::Update(dt);
}

void RenderingManager::Render(Scene* scene)
{
	// CHENG_LOG("Tex: ", std::to_string(Post.GetTexture()));
	if (!scene->GetCameraGameObject()->GetComponent<TransformComponent>())
	{
		DEFAULT_LOG("ERROR: NO CAMERA GAMEOBJECT");
		return;
	}
	//******************************* PRE RENDER PASS
	//*************************************
	RenderPassGPass(scene);
	//******************************* MAIN RENDER PASS
	//************************************
	RenderPassMain(scene);
	RenderQueued(scene);
	RenderPassPost(scene);
	RenderPassPost2(scene);
}
void RenderingManager::Resize(Vector3 size)
{
	Post.Init(size.x, size.y);
	Post2.Init(size.x, size.y);
}
void RenderingManager::RenderPassGPass(Scene* scene)
{
	m_renderPass = RENDER_PASS_PRE;
	m_lightDepthFBO.BindForWriting();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_gPassShaderID);
	//These matrices should change when light position or direction changes
	LightManager* lm = scene->GetLightManager();
	if (lm->GetSceneLights()[0]->type == Light::LIGHT_DIRECTIONAL)
		m_lightDepthProj.SetToOrtho(-SHADOW_VIEW_SIZE_X / 2, SHADOW_VIEW_SIZE_X / 2, -SHADOW_VIEW_SIZE_Y / 2, SHADOW_VIEW_SIZE_Y / 2, 0, SHADOW_VIEW_SIZE_Z / 2);
	else
		m_lightDepthProj.SetToPerspective(90, 1.f, 0.1, 20);
	Light* light = lm->GetSceneLights()[0];
	Vector3 pos = scene->GetPlayer()->GetComponent<TransformComponent>()->GetPosition();
	m_lightDepthView.SetToLookAt(
		pos.x, light->position.y, pos.z,
		-light->position.x, -light->position.y, -light->position.z,
		0, 1, 0);
	RenderWorld(scene);
}
void RenderingManager::RenderPassPost(Scene * scene)
{
	// glBindFramebuffer(GL_FRAMEBUFFER, 0);
	m_renderPass = RENDER_PASS_POST;
	glViewport(0, 0, Application::GetInstance().GetWindowWidth(), Application::GetInstance().GetWindowHeight());

	glUseProgram(m_PostProcessProgram);
	glUniform1f(m_parameters[U_EFFECT0_INTENSITY], (((float)(scene->GetPlayer()->GetComponent<EntityScript>()->GetValues()->GetHealth()) / (float)(scene->GetPlayer()->GetComponent<EntityScript>()->GetBaseStats()->GetMaxHealth()))));
	glUniform1f(m_parameters[U_EFFECT1_INTENSITY], SceneManager::GetInstance()->GetScene()->GetPlayer()->GetComponent<PlayerScript>()->GetTimeDead() - 1);
	glUniform1f(m_parameters[U_EFFECT1_TIME], Time::GetInstance()->GetElapsedTimeF());

	std::stringstream k;
	k << (((float)(scene->GetPlayer()->GetComponent<EntityScript>()->GetValues()->GetHealth()) / (float)(scene->GetPlayer()->GetComponent<EntityScript>()->GetBaseStats()->GetMaxHealth())));
	KZ_LOG("Intensity: ", k.str());
	glBindRenderbuffer(GL_RENDERBUFFER, m_PostBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Application::GetInstance().GetWindowWidth(), Application::GetInstance().GetWindowHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_PostBO);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//glDisable(GL_CULL_FACE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Post.BindForReading(GL_TEXTURE8);
	glDisable(GL_DEPTH_TEST);
	// meshList[GEO_POST_PROC_QUAD]->Render();
	Post2.BindForWriting();
	RenderPostQuad(scene);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_DEPTH_TEST);
}
void RenderingManager::RenderPassPost2(Scene* scene)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	m_renderPass = RENDER_PASS_POST;
	glViewport(0, 0, Application::GetInstance().GetWindowWidth(), Application::GetInstance().GetWindowHeight());

	glUseProgram(m_PostProcessProgram2);
	glUniform1f(m_parameters[U_EFFECT2_TIME], Time::GetInstance()->GetElapsedTimeF());
	glUniform1f(m_parameters[U_EFFECT2_INTENSITY], SceneManager::GetInstance()->GetScene()->GetPlayer()->GetComponent<PlayerScript>()->GetTimeDead() );

	glBindRenderbuffer(GL_RENDERBUFFER, m_PostBO2);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Application::GetInstance().GetWindowWidth(), Application::GetInstance().GetWindowHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_PostBO2);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//glDisable(GL_CULL_FACE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Post2.BindForReading(GL_TEXTURE8);
	glDisable(GL_DEPTH_TEST);
	// meshList[GEO_POST_PROC_QUAD]->Render();
	RenderPostQuad2(scene);
	glEnable(GL_DEPTH_TEST);
}
void RenderingManager::RenderPassMain(Scene* scene)
{
	m_renderPass = RENDER_PASS_MAIN;
	Post.BindForWriting();
	// glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Application::GetWindowWidth(),
		Application::GetWindowHeight());
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_programID);
	//pass light depth texture
	m_lightDepthFBO.BindForReading(GL_TEXTURE8);
	glUniform1i(m_parameters[U_SHADOW_MAP], 8);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// TODO Switch to loop
	LightManager* lm = scene->GetLightManager();
	for (unsigned i = 0; i < lm->GetSceneLights().size(); ++i)
	{
		Light* light = lm->GetSceneLights()[i];
		if (light->type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(light->position.x, light->position.y, light->position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_LightParameters[U_LIGHT_POSITION + i * U_LIGHT_TOTAL], 1, &lightDirection_cameraspace.x);
		}
		else if (light->type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * light->position;
			glUniform3fv(m_LightParameters[U_LIGHT_POSITION + i * U_LIGHT_TOTAL], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * light->spotDirection;
			glUniform3fv(m_LightParameters[U_LIGHT_SPOTDIRECTION + i * U_LIGHT_TOTAL], 1, &spotDirection_cameraspace.x);
		}
		else
		{
			Position lightPosition_cameraspace = viewStack.Top() * light->position;
			glUniform3fv(m_LightParameters[U_LIGHT_POSITION + i * U_LIGHT_TOTAL], 1, &lightPosition_cameraspace.x);
		}
	}

	GameObject* CameraObject = scene->GetCameraGameObject();
	Vector3 vCamPosition = CameraObject->GetComponent<TransformComponent>()->GetPosition();
	if (!CameraObject)
		return;
	Camera* Camera = scene->GetCamera();
	// TODO proper target == pos handling
	if (vCamPosition == Camera->m_vTarget)
	{
		vCamPosition.z += 1;
	}

	// Projection matrix
	Mtx44 projection;
	switch (CameraObject->GetComponent<CameraComponent>()->GetCameraType())
	{
	case CameraComponent::CAM_NONE:
		DEFAULT_LOG("Camera type not initialised.");
		__debugbreak();
		break;
	case CameraComponent::CAM_FIRST:
	case CameraComponent::CAM_CUSTOM_PERSPECT:
		projection.SetToPerspective(45, (float)Application::GetWindowWidth() / (float)Application::GetWindowHeight(), 0.1f, 10000);
		break;
	case CameraComponent::CAM_ORTHO:
	case CameraComponent::CAM_CUSTOM_ORTHO:
	{
		if (Camera->IsOrthoInit())
		{
			Vector3 vOrthoSize = Camera->GetOrthoSize();
			float height = vOrthoSize.x / ((float)Application::GetWindowWidth() / (float)Application::GetWindowHeight());
			projection.SetToOrtho(-vOrthoSize.x / 2, vOrthoSize.x / 2, -height / 2, height / 2, 0, vOrthoSize.z);
		}
		else
		{
			DEFAULT_LOG("(Cheng)Camera ortho size not initialsed.");
		}
	}
	break;
	default:
		DEFAULT_LOG("Camera type not unknown.");
		__debugbreak();
		break;
	}

	// Camera matrix
	viewStack.LoadIdentity();

	if (VIEW_AS_LIGHT)
	{
		Light* light = scene->GetLightManager()->GetSceneLights()[0];
		projection.SetToOrtho(-SHADOW_VIEW_SIZE_X / 2, SHADOW_VIEW_SIZE_X / 2, -SHADOW_VIEW_SIZE_Y / 2, SHADOW_VIEW_SIZE_X / 2, 0, SHADOW_VIEW_SIZE_Z / 2);
		viewStack.LookAt(
			light->position.x, light->position.y, light->position.z,
			0, 0, 0,
			0, 1, 0);
	}
	else
	{
		viewStack.LookAt(
			vCamPosition.x, vCamPosition.y, vCamPosition.z,
			Camera->m_vTarget.x, Camera->m_vTarget.y, Camera->m_vTarget.z,
			Camera->m_vUp.x, Camera->m_vUp.y, Camera->m_vUp.z);
	}
	projectionStack.LoadMatrix(projection);

	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	RenderWorld(scene);
}
void RenderingManager::RenderWorld(Scene* scene)
{
	Vector3 vCamPos = scene->GetCameraGameObject()->GetComponent<TransformComponent>()->GetPosition();
	Vector3 vCamDir = scene->GetCameraGameObject()->GetComponent<CameraComponent>()->GetCamera()->GetDir();

	GameObjectManager* GOM = scene->GetGameObjectManager();
	std::map<std::string, LayerData*>::iterator it;
	m_bFogEnabled = FOG_ENABLED;
	for (it = GOM->GetLayerList()->begin(); it != GOM->GetLayerList()->end(); it++)
	{
		// it->first == key
		// it->second == value
		// Switch shader
		if (it->first == "UI")
			continue;
		if (it->first == "Particle")
			continue;
		if (it->first == "Post")
			continue;
		if (it->first == "Post2")
			continue;
		if (SWITCH_SHADER && m_renderPass == RENDER_PASS_MAIN)
		{
			m_programID = it->second->GetShader();
			BindUniforms();
			SetUniforms(scene);
		}
		std::vector<GameObject*>* GOList = it->second->GetGOList();
		for (unsigned i = 0; i < GOList->size(); ++i)
		{
			GameObject* go = GOList->at(i);
			if (!go->IsActive())
				continue;
			Vector3 vCamPos = scene->GetCameraGameObject()->GetComponent<TransformComponent>()->GetPosition();
			RenderGameObject(go, vCamPos, false);
		}
	}
	// Render Particle
	if (m_renderPass == RENDER_PASS_PRE)
		return;
	m_bFogEnabled = false;
	std::map<std::string, LayerData*>* map = GOM->GetLayerList();
	std::vector<GameObject*>* GOListPart = map->at("Particle")->GetGOList();
	if (SWITCH_SHADER && m_renderPass == RENDER_PASS_MAIN)
	{
		m_programID = (*map)["Particle"]->GetShader();
		BindUniforms();
		SetUniforms(scene);
	}
	for (unsigned i = 0; i < GOListPart->size(); ++i)
	{
		GameObject* go = GOListPart->at(i);
		if (!go->IsActive())
			continue;

		RenderGameObject(go, vCamPos, true);
		for (unsigned i = 0; i < GOListPart->at(i)->GetChildList()->size(); ++i)
		{
			GameObject* goChild = GOListPart->at(i);
			if (!go->IsActive())
				continue;
			RenderGameObject(goChild, vCamPos, true);
		}
	}
	m_bFogEnabled = false;
	std::vector<GameObject*>* GOListUI = map->at("UI")->GetGOList();
	if (SWITCH_SHADER && m_renderPass == RENDER_PASS_MAIN)
	{
		m_programID = (*map)["UI"]->GetShader();
		BindUniforms();
		SetUniforms(scene);
	}
	for (unsigned i = 0; i < GOListUI->size(); ++i)
	{
		GameObject* go = GOListUI->at(i);
		if (!go->IsActive())
			continue;

		RenderGameObject(go, vCamPos, true);
	}
}
void RenderingManager::RenderPostQuad(Scene* scene)
{
	Vector3 vCamPos = scene->GetCameraGameObject()->GetComponent<TransformComponent>()->GetPosition();
	Vector3 vCamDir = scene->GetCameraGameObject()->GetComponent<CameraComponent>()->GetCamera()->GetDir();

	GameObjectManager* GOM = scene->GetGameObjectManager();
	std::map<std::string, LayerData*>* map = GOM->GetLayerList();
	std::vector<GameObject*>* GOListUI = map->at("Post")->GetGOList();
	if (SWITCH_SHADER && m_renderPass == RENDER_PASS_MAIN)
	{
		m_programID = (*map)["Render"]->GetShader();
		BindUniforms();
		SetUniforms(scene);
	}
	for (unsigned i = 0; i < GOListUI->size(); ++i)
	{
		GameObject* go = GOListUI->at(i);
		if (!go->IsActive())
			continue;
		// CHENG_LOG("", "Render");
		RenderGameObject(go, vCamPos, true);
	}
}

void RenderingManager::RenderPostQuad2(Scene* scene)
{
	Vector3 vCamPos = scene->GetCameraGameObject()->GetComponent<TransformComponent>()->GetPosition();
	Vector3 vCamDir = scene->GetCameraGameObject()->GetComponent<CameraComponent>()->GetCamera()->GetDir();

	GameObjectManager* GOM = scene->GetGameObjectManager();
	std::map<std::string, LayerData*>* map = GOM->GetLayerList();
	std::vector<GameObject*>* GOListUI = map->at("Post2")->GetGOList();
	if (SWITCH_SHADER && m_renderPass == RENDER_PASS_MAIN)
	{
		m_programID = (*map)["Render"]->GetShader();
		BindUniforms();
		SetUniforms(scene);
	}
	for (unsigned i = 0; i < GOListUI->size(); ++i)
	{
		GameObject* go = GOListUI->at(i);
		if (!go->IsActive())
			continue;
		// CHENG_LOG("", "Render");
		RenderGameObject(go, vCamPos, true);
	}
}
void RenderingManager::RenderGameObject(GameObject* go, Vector3 vCamPos, bool bIsUI, bool first)
{
	RenderComponent* renderComponent = go->GetComponent<RenderComponent>(true);
	if (renderComponent)
	{
		if (go->RENDER->GetRenderDistance() > 0)
		{
			if ((go->TRANS->GetPosition() - SceneManager::GetInstance()->GetScene()->GetPlayer()->TRANS->GetPosition()).Length() > go->RENDER->GetRenderDistance()) return;
		}
		bool isActive = renderComponent->IsActive();
		if (!isActive)
			return;
		Mesh* CurrentMesh = renderComponent->GetMesh();
		Mesh* MeshBiomed = renderComponent->GetMeshBiomed();
		AnimatedMesh* AnimatedMesh = renderComponent->GetAnimatedMesh();

		if (!CurrentMesh && !AnimatedMesh && !MeshBiomed)
		{
			DEFAULT_LOG("Mesh not initialised");
			return;
		}
		modelStack.PushMatrix();
		TransformComponent* trans = go->GetComponent<TransformComponent>();
		Vector3 vGameObjectPosition = trans->GetPosition();
		Vector3 vGameObjectRotation = trans->GetRotation();
		float fGameObjectRotationDegrees = trans->GetDegrees();
		Vector3 vGameObjectScale = trans->GetScale();

		modelStack.Translate(vGameObjectPosition.x, vGameObjectPosition.y, vGameObjectPosition.z);

		if (renderComponent->IsBillboard())
		{
			float rAngle = atan2((vCamPos.x - trans->GetPosition().x), (vCamPos.z - trans->GetPosition().z));
			float dAngle = Math::RadianToDegree(rAngle);

			modelStack.Rotate(dAngle, 0.f, 1.f, 0.f);
		}
		if (renderComponent->Is3DBillboard())
		{
			float fYaw = Math::RadianToDegree(atan2((vCamPos.x - trans->GetPosition().x), (vCamPos.z - trans->GetPosition().z)));
			Vector3 v = vCamPos - trans->GetPosition();
			Vector3 v1 = v;
			v.y = 0;
			float fPitch = AngleBetween(v, v1);

			modelStack.Rotate(fYaw, 0, 1, 0);
			modelStack.Rotate(-fPitch, 1, 0, 0);
		}
		if (fGameObjectRotationDegrees != 0 && !vGameObjectRotation.IsZero() && !renderComponent->Is3DBillboard())
			modelStack.Rotate(fGameObjectRotationDegrees, vGameObjectRotation.x, vGameObjectRotation.y, vGameObjectRotation.z);
		if (vGameObjectScale.x <= 0.05f || vGameObjectScale.y <= 0.05 || vGameObjectScale.z <= 0.05)
		{
			modelStack.PopMatrix();
			return;
		}
		modelStack.Scale(vGameObjectScale.x, vGameObjectScale.y, vGameObjectScale.z);
		if (!bIsUI)
		{
			if (CurrentMesh)
			{
				if (!renderComponent->IsText())
				{
					RenderMesh(renderComponent, go->GetComponent<RenderComponent>()->GetLightEnabled());
				}
				else
				{
					if (!renderComponent->IsTextOnScreen())
					{
						if (first)
							RenderQueue.push_back(go);
						else
							RenderText(renderComponent);
					}
					else
					{
						DEFAULT_LOG("Oof find haocheng plox");
					}
				}
			}

			else if (AnimatedMesh)
				RenderAnimatedMesh(renderComponent, go->GetComponent<RenderComponent>()->GetLightEnabled());

			else if (MeshBiomed)
				RenderBiomedMesh(renderComponent, go->GetComponent<BiomeComponent>(), go->GetComponent<RenderComponent>()->GetLightEnabled());
		}
		else
		{
			if (!renderComponent->IsText())
				RenderUI(renderComponent, go->GetComponent<RenderComponent>()->GetLightEnabled());
			else
			{
				if (!renderComponent->IsTextOnScreen())
				{
					if (first)
						RenderQueue.push_back(go);
					else
						RenderText(renderComponent);
				}
				else
					RenderTextOnScreen(renderComponent, renderComponent->GetText(), { renderComponent->GetMaterial().kAmbient.r,renderComponent->GetMaterial().kAmbient.g,renderComponent->GetMaterial().kAmbient.b },
						vGameObjectPosition.z, vGameObjectPosition.x, vGameObjectPosition.y);
			}
		}

		modelStack.PopMatrix();
	}
	for (unsigned i = 0; i < go->GetChildList()->size(); ++i)
	{
		GameObject* goChild = go->GetChildList()->at(i);
		if (!goChild->IsActive())
			continue;
		RenderGameObject(goChild, vCamPos, false);
	}
}
void RenderingManager::Exit()
{
	RenderingManagerBase::Exit();
}
Vector3 RenderingManager::MouseWorldDir()
{
	double x, y;
	Application::GetCursorPosRelative(&x, &y);
	Vector3 MousePosDevice((float)x * 2 - 1, -((float)y * 2 - 1));
	// CHENG_LOG("MOUSE Dev: ", vtos(MousePosDevice));
	// MousePosDevice = { 0,0,1 };
	Vector3 ClipCoord(MousePosDevice.x, MousePosDevice.y, -1.f);

	Mtx44 InvertProjection;
	try
	{
		InvertProjection = projectionStack.Top().GetInverse();
	}
	catch (const std::exception&)
	{
		return Vector3(0, 0, -1);
	}
	Vector3 EyeCoords = InvertProjection.Multi(ClipCoord, 1);
	EyeCoords.z = -1;
	Mtx44 InvertView = viewStack.Top().GetInverse();
	Vector3 WorldSpace = InvertView.Multi(EyeCoords, 0);
	WorldSpace.Normalize();
	// CHENG_LOG("MOUSE DIR: ", vtos(WorldSpace));
	return WorldSpace;
}