#pragma once

#include "Texture.h"
#include <vector>

class Score : public GameObject
{
private:
	std::vector<Texture*> mScore;

public:
	Score();
	~Score();


	void SetScore(int score);
	void Render();

private:
	void ClearScore();

};

