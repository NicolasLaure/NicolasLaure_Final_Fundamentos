#pragma once
#include "GameData.h"

void PlayerAttack(GameData& gd);

void SwordUpdate(GameData& gd);
bool isEnemyHitted(GameData& gd, Vector2 attackedPosition);
void RangedAttackExplosion(GameData& gd, Vector2 lastAttackedPosition);
void CleanExplosion(GameData gd, Vector2 lastAttackedPosition);

void TakeItem(GameData& gd);