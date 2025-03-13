#include "CheckPoint.h"

void CheckPoint::OnInitialize()
{
	mShape.setOrigin(mShape.getGlobalBounds().width / 2, mShape.getGlobalBounds().height / 2);
}

void CheckPoint::OnUpdate()
{

}
