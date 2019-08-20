#pragma once
class Stats
{
	friend class EntityScript;
private:
	//
	int m_iHealthMax;
	int m_iHealthRegenRate;
	float m_fStaminaMax;
	float m_fStaminaRegenRate;
	// movement
	float m_fMaxMovementSpeed;
	float m_fMovementForce;
	float m_fJumpForce;

	float m_fDetectionRadius;
public:
	Stats();
	Stats(int iHealthMax, int iHealthRegenRate = 0, float StaminaMax = 100, 
		float fStaminaRegenRate = 20, float MovementMax = 100, float MovementForece = 40, 
		float DetectionRatius = 8);
	~Stats();

	void SetZero();
	void SetOne();

	void SetMaxHealth(int i);
	int GetMaxHealth() const;
	void SetMaxStamina(float f);
	float GetMaxStamina() const;
	void SetStaminaRegen(float f);
	void SetMovement(float max, float force);
	void AffectMaxStamina(float f);
	void AffectStaminaRegenRate(float f);

	float GetDetectionRadius() const;
};
