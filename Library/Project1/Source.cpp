#include <stdio.h>
#include <EventManager.h>

class TestExecuter : public Lib::Event
{
public:
	TestExecuter();
	~TestExecuter();
	enum EventID
	{
		NONE
	};

private:
	void Action(int _eventId);
};

TestExecuter::TestExecuter()
{
}

TestExecuter::~TestExecuter()
{
}

void TestExecuter::Action(int _eventId)
{
	switch (_eventId)
	{
	case 1:
		printf("Action1‚ªŒÄ‚Î‚ê‚½‚æ\n");
		break;
	case 2:
		printf("Action2‚ªŒÄ‚Î‚ê‚½‚æ\n");
		break;
	case 3:
		printf("Action3‚ªŒÄ‚Î‚ê‚½‚æ\n");
		break;
	}
}

void main()
{
	TestExecuter* var = new TestExecuter();
	Lib::EventManager::GetInstance()->AddEvent("test",var);
	Lib::EventManager::GetInstance()->AddEvent("test", var);

	Lib::EventManager::GetInstance()->CallEvent("test",TestExecuter::NONE);
	delete var;
	while (1);
}