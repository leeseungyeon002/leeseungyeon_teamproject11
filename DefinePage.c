#include"DefinePage.h"

void PrintHomepage()
{
	setFullscreen();
	system("cls");
	PrintStatusbar();
	PrintHomeButton();
	PrinttodayCalendar();
	Print_MainMenu(0);
	Select_Menu();
}

Select_Menu()
{
	int ch;
	int menu = 1;
	COORD tmp;
	getMenusize();

	while (1)
	{
		if (kbhit())
		{
			ch = getch();

			if (ch == 0xE0 || ch == 0)
			{
				ch = getch();
				switch (ch)
				{
				case DOWN_KEY:
					menu++;
					if (menu > MenuNum)
						menu = 1;
					Print_MainMenu(menu);
					break;
				case UP_KEY:
					menu--;
					if (menu < 1)
						menu = MenuNum;
					Print_MainMenu(menu);
					break;
				}
			}
			else
			{
				switch (ch)
				{
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
					menu = (int)(ch - '0');
					tmp.X = pos_start.X + 3 + strlen("메뉴 번호를 입력해주세요 : ");
					tmp.Y = pos_start.Y + 2;
					gotoxy(tmp.X, tmp.Y); printf("%d", menu);
					Print_MainMenu(menu);
					break;
				case TAP_KEY:
					if (menu >= 1 && menu <= 5)
						menu = getselectdaybutton;
					else if (menu == getselectdaybutton)
					{
						menu = gettodaybutton;
						Print_MainMenu(-1);
						textcolor(WHITE, DARKGRAY); PrinttodaydateButton();
						textcolor(WHITE, BLACK); PrintSelectdateButton();
					}
					else if (menu == gettodaybutton)
					{
						menu = getselectdaybutton;
						Print_MainMenu(-1);
						textcolor(WHITE, DARKGRAY); PrintSelectdateButton();
						textcolor(WHITE, BLACK); PrinttodaydateButton();
					}
					break;
				case ENTER_KEY:
					switch (menu)
					{
					case 1:
						Staff();
						break;
					case 2:
						Schedule();
						break;
					case 3:
						Work();
						break;
					case 4:
						system("cls");
						if (MessageBox(NULL, TEXT("종료하시겠습니까?"), TEXT("Check Box"), MB_YESNO | MB_ICONQUESTION) == IDYES)
							exit(0);
						exit(0);
						break;
					case getselectdaybutton:
						GetSelectedday(selected_day);
						PrinttselectedCalendar();
						break;
					case gettodaybutton:
						PrinttodayCalendar();
						break;
					}
				}
			}
		}
	}
}

void PrintStaffpage()
{
	PrintStatusbar();
	Staff();
}