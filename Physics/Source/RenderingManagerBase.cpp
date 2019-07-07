#include "RenderingManagerBase.h"
#include "DataContainer.h"
#include "Locator.h"
#include "Application.h"

RenderingManagerBase::RenderingManagerBase()
{
	m_fElapsedTime = 0;
	m_DepthQuad =
		MeshBuilder::GenerateQuad("LIGHT_DEPTH_TEXTURE", Color(1, 1, 1), 1.f);
	m_iNumOfLightVar = 11;
	m_DepthQuad->m_uTextureArray[0] =
		m_lightDepthFBO.GetTexture();
}

RenderingManagerBase::~RenderingManagerBase()
{

}

void RenderingManagerBase::BindUniforms()
{
	// Get a handle for our uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	//m_parameters[U_MODEL] = glGetUniformLocation(m_programID, "M");
	//m_parameters[U_VIEW] = glGetUniformLocation(m_programID, "V");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	// Fog
	m_parameters[U_FOG_COLOR] = glGetUniformLocation(m_programID, "fogParam.color");
	m_parameters[U_FOG_START] = glGetUniformLocation(m_programID, "fogParam.start");
	m_parameters[U_FOG_END] = glGetUniformLocation(m_programID, "fogParam.end");
	m_parameters[U_FOG_DENSITY] = glGetUniformLocation(m_programID, "fogParam.density");
	m_parameters[U_FOG_TYPE] = glGetUniformLocation(m_programID, "fogParam.type");
	m_parameters[U_FOG_ENABLED] = glGetUniformLocation(m_programID, "fogParam.enabled");

	m_parameters[U_FRAG_ET] = glGetUniformLocation(m_programID, "frag_et");
	m_parameters[U_VERT_ET] = glGetUniformLocation(m_programID, "vert_et");

	//texture
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID,
		"colorTextureEnabled[0]");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture[0]");

	m_parameters[U_COLOR_TEXTURE_ENABLED1] = glGetUniformLocation(m_programID,
		"colorTextureEnabled[1]");
	m_parameters[U_COLOR_TEXTURE1] = glGetUniformLocation(m_programID, "colorTexture[1]");

	m_parameters[U_COLOR_TEXTURE_ENABLED1] = glGetUniformLocation(m_programID,
		"colorTextureEnabled[2]");
	m_parameters[U_COLOR_TEXTURE1] = glGetUniformLocation(m_programID, "colorTexture[2]");

	// Shadows
	m_parameters[U_LIGHT_DEPTH_MVP] =
		glGetUniformLocation(m_programID, "lightDepthMVP");
	m_parameters[U_SHADOW_MAP] = glGetUniformLocation(m_programID,
		"shadowMap");
	m_parameters[U_LIGHT_DEPTH_MVP_GPASS] =
		glGetUniformLocation(m_gPassShaderID, "lightDepthMVP");
	glUseProgram(m_programID);

	// Rebind light param
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	// Init fog
	Color fogColor{ 0.5f, 0.5f, 0.5f };

	glUniform3fv(m_parameters[U_FOG_COLOR], 1, &fogColor.r);
	glUniform1f(m_parameters[U_FOG_START], 1);
	glUniform1f(m_parameters[U_FOG_END], 1000);
	glUniform1f(m_parameters[U_FOG_DENSITY], 0.005f);
	glUniform1i(m_parameters[U_FOG_TYPE], 1);
	glUniform1i(m_parameters[U_FOG_ENABLED], true);

	// Shadows
	glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP_GPASS], 1,
		GL_FALSE, &m_lightDepthMVPGPass.a[0]);
	glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP], 1,
		GL_FALSE, &m_lightDepthMVP.a[0]);

	glUniform1i(m_parameters[U_SHADOW_MAP], 8);

	glUniform1f(m_parameters[U_VERT_ET], m_fElapsedTime);
	glUniform1f(m_parameters[U_FRAG_ET], m_fElapsedTime);

	CHENG_LOG("Time: ", std::to_string(m_fElapsedTime));
	// Use our shader
}
void RenderingManagerBase::Init()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Shadows--------------------------------------------------------------------------------
	m_gPassShaderID = DataContainer::GetInstance()->GetShader("GPass");

	// Main Shader--------------------------------------------------------------------------------
	m_programID = DataContainer::GetInstance()->GetShader("Default");

	// Shadows
	m_lightDepthFBO.Init(2048, 2048);

	BindUniforms();

	// Init fog
	Color fogColor{ 0.5f, 0.5f, 0.5f };

	glUniform3fv(m_parameters[U_FOG_COLOR], 1, &fogColor.r);
	glUniform1f(m_parameters[U_FOG_START], 1);
	glUniform1f(m_parameters[U_FOG_END], 1000);
	glUniform1f(m_parameters[U_FOG_DENSITY], 0.005f);
	glUniform1i(m_parameters[U_FOG_TYPE], 1);
	glUniform1i(m_parameters[U_FOG_ENABLED], true);

	int tmp = 10.f;
	int tmp2 = 0;
	for (std::vector<Light*>::iterator it = m_LightManager.GetSceneLights().begin(); it != m_LightManager.GetSceneLights().end(); ++it)
	{
		Light* L = static_cast<Light*>(*it);
		L->position.Set(0.01f + tmp * tmp2, 30, 0);
		L->color.Set(1, 1, 1);
		L->power = 1;
		L->kC = 1.f;
		L->kL = 0.01f;
		L->kQ = 0.001f;
		L->cosCutoff = cos(Math::DegreeToRadian(45));
		L->cosInner = cos(Math::DegreeToRadian(30));
		L->exponent = 3.f;
		L->spotDirection.Set(0.f, 1.f, 0.f);
		tmp2++;
	}

	glUniform1i(m_parameters[U_NUMLIGHTS], SCENELIGHTS.size());
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	for (int index = 0; index < m_LightManager.GetSceneLights().size(); ++index)
	{
		Light* L = SCENELIGHTS[index];
		glUniform1i(m_parameters[U_LIGHT0_TYPE + (m_iNumOfLightVar * index)], L->type);
		glUniform3fv(m_parameters[U_LIGHT0_COLOR + (m_iNumOfLightVar * index)], 1, &L->color.r);
		glUniform1f(m_parameters[U_LIGHT0_POWER + (m_iNumOfLightVar * index)], L->power);
		glUniform1f(m_parameters[U_LIGHT0_KC + (m_iNumOfLightVar * index)], L->kC);
		glUniform1f(m_parameters[U_LIGHT0_KL + (m_iNumOfLightVar * index)], L->kL);
		glUniform1f(m_parameters[U_LIGHT0_KQ + (m_iNumOfLightVar * index)], L->kQ);
		glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF + (m_iNumOfLightVar * index)], L->cosCutoff);
		glUniform1f(m_parameters[U_LIGHT0_COSINNER + (m_iNumOfLightVar * index)], L->cosInner);
		glUniform1f(m_parameters[U_LIGHT0_EXPONENT + (m_iNumOfLightVar * index)], L->exponent);
	}

	bLightEnabled = true;
	BindUniforms();
}
void RenderingManagerBase::UpdateLightUniforms(int index)
{
	Light* L = SCENELIGHTS[index];
	glUniform1i(m_parameters[U_LIGHT0_TYPE + (m_iNumOfLightVar * index)], L->type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR + (m_iNumOfLightVar * index)], 1, &L->color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER + (m_iNumOfLightVar * index)], L->power);
	glUniform1f(m_parameters[U_LIGHT0_KC + (m_iNumOfLightVar * index)], L->kC);
	glUniform1f(m_parameters[U_LIGHT0_KL + (m_iNumOfLightVar * index)], L->kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ + (m_iNumOfLightVar * index)], L->kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF + (m_iNumOfLightVar * index)], L->cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER + (m_iNumOfLightVar * index)], L->cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT + (m_iNumOfLightVar * index)], L->exponent);
}
void RenderingManagerBase::Update(double dt)
{ 
	//Keyboard Section
	// TODO SET DRAW MODE

	//if (Application::IsKeyPressed('1'))
	//	glEnable(GL_CULL_FACE);
	//if (Application::IsKeyPressed('2'))
	//	glDisable(GL_CULL_FACE);
	//if (Application::IsKeyPressed('3'))
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//if (Application::IsKeyPressed('4'))
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Add or remove light
	//NOTE: POSITION IS DEFAULT 0,0,0
	if (Application::IsKeyPressed('1'))
	{
		m_LightManager.AddLight();
		glUniform1i(m_parameters[U_NUMLIGHTS], SCENELIGHTS.size());
	}
	if (Application::IsKeyPressed('0'))
	{
		m_LightManager.RemoveLight();
		glUniform1i(m_parameters[U_NUMLIGHTS], SCENELIGHTS.size());
	}

	//Change current light type
	if (Application::IsKeyPressed('7'))
	{
		CURRENTLIGHT->type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE + (m_iNumOfLightVar * LIGHTINDEX)], CURRENTLIGHT->type);
	}
	if (Application::IsKeyPressed('8'))
	{
		CURRENTLIGHT->type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE + (m_iNumOfLightVar * LIGHTINDEX)], CURRENTLIGHT->type);
	}
	if (Application::IsKeyPressed('9'))
	{
		CURRENTLIGHT->type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE + (m_iNumOfLightVar * LIGHTINDEX)], CURRENTLIGHT->type);
	}

	//Cycle Light
	static bool isCyclingLight = false;
	if (!isCyclingLight && (Application::IsKeyPressed('M') || Application::IsKeyPressed('N')))
	{
		isCyclingLight = true;
		if (Application::IsKeyPressed('M'))
		{
			CYCLELIGHT_FOWARD;
		}
		if (Application::IsKeyPressed('N'))
		{
			CYCLELIGHT_BACK;
		}

		UpdateLightUniforms(LIGHTINDEX);
	}
	else if(isCyclingLight && (!Application::IsKeyPressed('M') || !Application::IsKeyPressed('N')))
		isCyclingLight = false;

	fps = (float)(1.f / dt);
	m_fElapsedTime += (float)dt;
}

void RenderingManagerBase::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->m_uTextureArray[0] <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->m_uTextureArray[0]);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void RenderingManagerBase::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->m_uTextureArray[0] <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->m_uTextureArray[0]);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}
void RenderingManagerBase::RenderUI(Mesh* mesh, bool enableLight)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 1920, 0, 1080, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	//Shadows
	if (m_renderPass == RENDER_PASS_PRE)
	{
		/*Mtx44 lightDepthMVP = m_lightDepthProj *
			m_lightDepthView * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP_GPASS], 1,
			GL_FALSE, &lightDepthMVP.a[0]);
		mesh->Render();*/
		return;
	}
	//--

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
		//Shadows--
		/*Mtx44 lightDepthMVP = m_lightDepthProj *
			m_lightDepthView * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP], 1,
			GL_FALSE, &lightDepthMVP.a[0]);*/
			//--
			//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (mesh->m_uTextureArray[i] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->m_uTextureArray[i]);
			glUniform1i(m_parameters[U_COLOR_TEXTURE + i], i);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}
	mesh->Render();
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (mesh->m_uTextureArray[i] > 0)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	projectionStack.PopMatrix();
	viewStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void RenderingManagerBase::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	glEnable(GL_DEPTH_TEST);
	//Shadows
	if (m_renderPass == RENDER_PASS_PRE)
	{
		m_lightDepthMVPGPass = m_lightDepthProj *
			m_lightDepthView * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP_GPASS], 1,
			GL_FALSE, &m_lightDepthMVPGPass.a[0]);
		mesh->Render();
		return;
	}
	//--

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
		//Shadows--
		m_lightDepthMVP = m_lightDepthProj *
			m_lightDepthView * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_LIGHT_DEPTH_MVP], 1,
			GL_FALSE, &m_lightDepthMVP.a[0]);
		//--
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (mesh->m_uTextureArray[i] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->m_uTextureArray[i]);
			glUniform1i(m_parameters[U_COLOR_TEXTURE + i], i);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}
	mesh->Render();
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (mesh->m_uTextureArray[i] > 0)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

void RenderingManagerBase::Render(Scene* scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderingManagerBase::Exit()
{
	// Cleanup VBO
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_gPassShaderID);
}