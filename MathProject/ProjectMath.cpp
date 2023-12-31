#include <iostream>
#include <cstdlib>
#include<string>
#include <cmath>
#include <iomanip>


using namespace std;

enum enQuestionLevel
{
	Easy = 1, Med = 2 , Hard = 3 , Mix = 4
};

enum enOperationType
{
	Add = 1 , Sub = 2 , Mul = 3 , Div = 4 , Mix1 = 5
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

int ReadPositiveNumber()
{
	int QuestionsNumber = 0;

	do
	{
	cout << "How many question do you want to answer? ";
	cin >> QuestionsNumber;

	} while (QuestionsNumber < 0 || QuestionsNumber > 100);

	return QuestionsNumber;

}


struct stQuestion
{
	short Number1;
	short Number2;
	enOperationType Operation;
	enQuestionLevel QuestionLevel;
	short RightAnswer = 0;
	short UserAnswer = 0;
	bool isRightAnswer = false;
	short NumberOfQuestion = 0;
	string Question = "";
	

};

struct stQuizze
{
	stQuestion QuestionList[100];
	enOperationType OpType;
	enQuestionLevel QuestonLevel;
	short NumberOfQuestion = 0;
	short NumberOfRightAnswer = 0;
	short NumberOfWrongAnswer = 0;
	bool IsPass = false;
};

char GetOperationType(enOperationType OperationType)
{

	char Operations[4] = { '+' ,'-' , '*' ,'/' };

	return Operations[OperationType - 1];
}

short  WhichQuestionLevel()
{

	short QuestionLevel = 1;
	cout << "\nChoice Level of the Question  1:[Easy],  2:[Med],  3:[Hard],  4:[Mix]: ";
	cin >> QuestionLevel;

	return QuestionLevel;

}

int UserAnswer()
{
	int userAnswer;
	cout << "Please enter your Answer: ";
	cin >> userAnswer;

	return userAnswer;
}
enQuestionLevel ChoiceQuestionLevel()
{

	short QuestioKind = WhichQuestionLevel();

	switch (QuestioKind)
	{
	case enQuestionLevel::Easy:
		return enQuestionLevel::Easy;
		break;
	case enQuestionLevel::Med:
		return enQuestionLevel::Med;
		break;
	case enQuestionLevel::Hard:
		return enQuestionLevel::Hard;
		break;
	default :
		return enQuestionLevel::Mix;
		break;
	}
}

enOperationType GenerateRandomOperation(stQuestion &Question)
{
	return Question.Operation = (enOperationType)RandomNumber(1, 4);

}


int Calculate(stQuestion Question , enOperationType OperationType)


{

	
	switch (OperationType)
	{
	case Add:
		return Question.Number1 + Question.Number2;
		break;
	case Sub:
		return Question.Number1 - Question.Number2;
		break;
	case Mul:
		return Question.Number1 * Question.Number2;
		break;
	case Div:
		return Question.Number1 / Question.Number2;
		break;
	}


}

bool isRightAnswer(stQuestion Question)
{
	return Question.RightAnswer == Question.UserAnswer;
}

int GenerateNumber(enQuestionLevel QuestionLevel )
{

	short Number = 0;

	if (QuestionLevel == enQuestionLevel::Easy)
		return Number = RandomNumber(0, 10);

	else if (QuestionLevel == enQuestionLevel::Med)
		return Number = RandomNumber(10, 50);

	else if (QuestionLevel == enQuestionLevel::Hard)
		return Number = RandomNumber(50, 100);

	else
		return Number = RandomNumber(0, 100);
}
enOperationType GenerateOperation( )
{
	
	int OperationType = 0;
	cout << "\nchoice a Number for an operation 1:[+],  2:[-],  3 :[*],  4:[/],  5:[Mix]: ";
	cin >>OperationType;
	return (enOperationType)OperationType;

}



void ConceptionQuestion(stQuestion Question)

{

	cout << Question.Number1 <<GetOperationType(Question.Operation) << Question.Number2<<endl;

}
void RoundInfo(stQuestion QuestionInfo , short HowManyQuestion , stQuizze &quiez)

{
	// if the user gets a correct answer , the screen will turn green else red 
		

	if (QuestionInfo.isRightAnswer == true)
	{
		cout << " \nYour Answer is correct:)\n\n";
		 system("color 2f"); 
		 quiez.NumberOfRightAnswer++;  
		 
	}
	else
	{
		cout << "\n Your  Answer is Wrong:(!\n";
		cout << "this the right answer: "<< QuestionInfo.RightAnswer << endl<<endl;
	system("color 4F");
	quiez.NumberOfWrongAnswer++;

	}

}


void headingGameOver() {
	cout << setw(92) << "|------------------------------------------------------------|\n";
	cout << setw(92) << "|                          Game Over                         |\n";
	cout << setw(92) << "|------------------------------------------------------------|\n";

}

string isPass(stQuizze quiz)
{
	if (quiz.NumberOfRightAnswer >= quiz.NumberOfWrongAnswer)
		return "You Pass";

	return "You Fail";
}

void InterfaceGameOver( stQuizze quiz )
{

	cout <<setw(30) << "|" << setw(30) << "you answered wrong|" << setw(30) << quiz.NumberOfWrongAnswer << "|\n";
	cout <<setw(30) << "|" << setw(30) << "you answered right |" << setw(30) << quiz.NumberOfRightAnswer << "|\n";
	cout <<setw(30) << "|" << setw(30) << "final result|" << setw(30) << isPass(quiz) << "|\n";
	cout <<setw(92) << "|------------------------------------------------------------|\n";
	cout <<setw(92) << "|                        thank you :)                        |\n";
	cout <<setw(92) << "|------------------------------------------------------------|\n";

}



void PlayGame(int HowManyQuestion, enQuestionLevel  QuestionLevel, enOperationType  OperationType)
{

	

	stQuestion Question;
	stQuizze quiz;

	for (int NumberOfQuestions = 1; NumberOfQuestions <= HowManyQuestion; NumberOfQuestions++)
	{

		Question.Number1 = GenerateNumber(QuestionLevel);
		Question.Number2 = GenerateNumber(QuestionLevel);
		if (OperationType == enOperationType::Mix1)
		{
			GenerateRandomOperation(Question);
		}
		else
			Question.Operation = OperationType;
			

		cout << "\nQuestion [" << NumberOfQuestions << "/" << HowManyQuestion << "]: ";
		ConceptionQuestion(Question);

		Question.RightAnswer = Calculate(Question, Question.Operation);

		Question.UserAnswer = UserAnswer();
		Question.isRightAnswer = isRightAnswer(Question);
		Question.NumberOfQuestion = NumberOfQuestions;

		RoundInfo(Question, HowManyQuestion ,quiz);

	}

	headingGameOver();

	InterfaceGameOver(quiz);

}


void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		system("cls");
		system("color 0f");
	short NumberOfQuestion = ReadPositiveNumber();
	enQuestionLevel QuestionLevel = ChoiceQuestionLevel();
		 PlayGame(NumberOfQuestion,QuestionLevel , GenerateOperation());

		cout << "\nDo you want to play again? Y/N: ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}
int main() {

	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}