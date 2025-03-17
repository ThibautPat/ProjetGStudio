#include "Checkpoint.h"

void Checkpoint::OnInitialize()
{
	mShape.setOrigin(mShape.getGlobalBounds().width / 2, mShape.getGlobalBounds().height / 2);
}

void Checkpoint::OnUpdate()
{
}
