#pragma once
class ScoreManager
{

public:

	static ScoreManager* instance();
	
	~ScoreManager();

	void set_score(const int& score);

	int score() const;
	int high_score() const;


private:

	static ScoreManager* instance_;

	int score_;
	int high_score_;

	ScoreManager();

};

