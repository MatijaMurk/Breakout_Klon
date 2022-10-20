#include "Score.h"

Score::Score() {

	SetScore(0);

}

Score::~Score() {

	ClearScore();
}

void Score::ClearScore(){
	
	for (int i = 0; i < mScore.size(); i++) {
		delete mScore[i];
		mScore[i] = NULL;
	}

	mScore.clear();

}

void Score::SetScore(int score) {

	ClearScore();

	if (score == 0) {

		for (int i = 0; i < 3; i++) {
			mScore.push_back(new Texture("0", "Prototype.ttf", 32, { 240,240,240 }));
			mScore[i]->Parent(this);
			mScore[i]->Position(Vector2(-32.0f * i, 0.0f));
		}
	}
	else {
		std::string str = std::to_string(score);
		int lastIndex = static_cast<int>(str.length() - 1);

		for (int i = 0; i <= lastIndex; i++) {
			mScore.push_back(new Texture(str.substr(i, 1), "Prototype.ttf", 32, { 240,240,240 }));
			mScore[i]->Parent(this);
			mScore[i]->Position(Vector2(-32.0f * (lastIndex - i), 0.0f));
		}
	}
}

void Score::Render() {

	for (int i = 0; i < mScore.size(); i++) {
		mScore[i]->Render();
	}

}
