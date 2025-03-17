#include "DeadlyObstacle.h"

void DeadlyObstacle::OnInitialize()
{
	mShape.setOrigin(mShape.getGlobalBounds().width / 2, mShape.getGlobalBounds().height / 2);
}

void DeadlyObstacle::OnUpdate()
{

}
