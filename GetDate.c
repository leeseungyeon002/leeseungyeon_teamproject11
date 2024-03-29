#include"GetDate.h"

// 함수
void GetToday()
{
	time_t timer;
	struct tm* t;

	timer = time(NULL); // 현재 시각을 초 단위로 얻기
	t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

	today.tm_year = (t->tm_year + 1900);
	today.tm_mon = (t->tm_mon + 1);
	today.tm_day = (t->tm_mday);
	GetDay(today);
}

//http://mwultong.blogspot.com/2006/10/c-current-date-time.html

void GetSelectedday(ldate date)
{
	char buf[11];
	int cnt = 0, key;  // 입력 받은 글자 수와 키 

	PrinttSelectdateInputbox();

	key = getch();  // 한 글자 입력받음
	buf[cnt++] = (char)key;   // 버퍼에 글자 저장하고 카운트 1 증가
	PrinttSelectdateInputbox_beinput();
	gotoxy(pos_start.X, pos_start.Y);
	putchar("%c", buf[cnt]);  // 화면에 별 표시 

	while (1)
	{
		key = getch();  // 한 글자 입력받음

		if (key == ENTER_KEY)  // 엔터 키면 종료
			break;

		buf[cnt++] = (char)key;   // 버퍼에 글자 저장하고 카운트 1 증가  
		putchar("%c", buf[cnt]);

		if (cnt == 10)  // 최대 크기를 넘어가면 종료 
			break;
	}
	date.tm_year = 1000 * buf[0] + 100 * buf[1] + 10 * buf[2] + buf[3];

	if (buf[6] == '-')
	{
		date.tm_mon = buf[5];

		if (buf[8] == '\n')
			date.tm_day = buf[7];
		else
			date.tm_day = 10 * buf[7] + buf[8];
	}
	else
	{
		date.tm_mon = 10 * buf[5] + buf[6];

		if (buf[9] == '\n')
			date.tm_day = buf[8];
		else
			date.tm_day = 10 * buf[8] + buf[9];
	}
}

void GetMonthDay(ldate date)
{
	switch (date.tm_mon)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		monthday = 31;
		break;

	case 4: case 6: case 9: case 11:
		monthday = 30;
		break;

	case 2:
		if (date.tm_year % 4 == 0 && date.tm_year % 100 != 0 || date.tm_year % 400 == 0)
			monthday = 29;
		else
			monthday = 28;
		break;

	default:
		monthday = 0;
	}
}

void GetWeekDay(ldate date, int day)
{
	if (date.tm_mon == 1 || date.tm_mon == 2) {
		date.tm_year--;
		date.tm_mon += 12;
	}
	weekday = (date.tm_year + date.tm_year / 4 - date.tm_year / 100 + date.tm_year / 400 + (13 * date.tm_mon + 8) / 5 + day) % 7;
}
// https://cafe.naver.com/cafec/165808

void GetDay(ldate date)
{
	GetMonthDay(date);
	GetWeekDay(date, 1);
}