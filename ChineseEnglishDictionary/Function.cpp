#include "Dictionary.h"

/*
δ��ɣ�

1.ǿ������--- ��дǿ�����亯��
2.Ӣ���ѯ---Ӣ��ȫ��ѯ����
3.���Ĳ�ѯ---����һ�£����ܲ�����������Χ֮��
*/

int main()
{
	setlocale(LC_ALL, "");
	initgraph(1000, 600);
	// ��ȡ���ھ��
	HWND hwnd = GetHWnd();
	//�����������ڴ���
	SetWindowText(hwnd, _T("CET4Ӣ���ʵ�"));
	//������ͼ��ʼ
	BeginBatchDraw();
	loadimage(&imgMenu, _T("C:\\Users\\ztlzl\\Desktop\\CE-Dict\\bk.jpg"));
	init();
	readWord();//���ú������ļ��ж�ȡ���ʴ���ṹ������
	writeWord();//���ú����ѽṹ������������Զ����Ƶ���ʽ��ŵ��ļ���
	MOUSEMSG m;
	loop:putimage(0, 0, &imgMenu);
	FlushBatchDraw();
	while (1)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			//��������
			if (m.mkLButton == true)
			{
				//���������������ı��ļ�
				if (m.x > 393 && m.x < 600 && m.y > 27 && m.y < 113)
				{
					loadWordTxt();
				}
				//����������������ʷ����
				else if (m.x > 393 && m.x < 603 && m.y > 161 && m.y < 256)
				{
					loadHistoryData();
				}
				//���������˴˴����ݴ浵
				else if (m.x > 392 && m.x < 604 && m.y > 304 && m.y < 384)
				{
					saveThisData();
				}
				//���������˵������
				else if (m.x > 389 && m.x < 608 && m.y > 427 && m.y < 514)
				{
					BrowseWords();
					if (isReturnBrowseWords == 1)
					{
						isReturnBrowseWords = 0;
						goto loop;
					}
				}
				//���������˵��ʱ���
				else if (m.x > 670 && m.x < 875 && m.y > 26 && m.y < 107)
				{
					reciteWords();
					if (isReturnReciteWords == 1)
					{
						isReturnReciteWords = 0;
						goto loop;
					}
				}
				//���������˵��ʲ���
				else if (m.x > 672 && m.x < 869 && m.y > 161 && m.y < 251)
				{
					testWordsInit();
					if (isReturnTestWords == 1)
					{
						isReturnTestWords = 0;
						goto loop;
					}
				}
				//���������˵��ʲ�ѯ
				else if (m.x > 669 && m.x < 876 && m.y > 304 && m.y < 385)
				{

				}
				//���������˵��ʱ�
				else if (m.x > 662 && m.x < 879 && m.y > 428 && m.y < 512)
				{
					wordsBook();
					if (isReturnWordsBook == 1)
					{
						isReturnWordsBook = 0;
						goto loop;
					}
				}
				//����������EXIT
				else if (m.x > 897 && m.x < 995 && m.y > 8 && m.y < 46)
				{
					MessageBox(GetHWnd(), "     �ڴ������´�ʹ��", "CET4Ӣ���ʵ�", MB_OK);
					exit(0);
				}
			}
		}
	}
	EndBatchDraw();
	return 0;
}

void readWord()
{
	FILE* wordFile;
	if ((wordFile = fopen("C:\\Users\\ztlzl\\Desktop\\cet4.txt", "rt"))
		== NULL) {
		printf("Can not open the file!");
		exit(0);
	}
	char s[120];
	int i = 0, j = 0;
	int wordCnt = 0;
	while ((fgets(s, 100, wordFile)) != NULL)
		//һ��һ�еĶ�ȡ�ļ�����������ɽṹ������ĸ�ֵ
	{
		i = 0;
		j = 0;
		if ((isalpha(s[0]) != 0) && (isalpha(s[1]) != 0))//����Ϊ������
		{
			while (s[i] != 32)//ֱ������һ�еĿո�Ҳ���ǰѵ��ʶ���
			{
				(word[wordCnt]).English[j++] = s[i++];
			}
			(word[wordCnt]).English[j] = '\0';//��֤�ַ�����\0��β
			j = 0;
			while (s[i] != '\n')
				//ֱ������һ�е�ĩβ��Ҳ���ǰ������������
			{
				(word[wordCnt]).Chinese[j++] = s[i++];
			}
			(word[wordCnt]).Chinese[j] = '\0';//��֤�ַ�����\0��β
			wordCnt++;
		}
	}
	fclose(wordFile);
}

void writeWord()
{
	FILE *fp;
	if ((fp = fopen("C:\\Users\\ztlzl\\Desktop\\binaryCet4.txt", "wb+"))
		== NULL) {//��д�������ı�
		printf("Can not open the file!");
		exit(0);
	}
	fwrite(word, sizeof(Word), 3665, fp);
	fclose(fp);
}

void init()
{
	//��ÿ�����ʽṹ�����������ֵ
	for (int i = 0; i < 3665; i++)
	{
		word[i].index = i;
		word[i].isInWordsBook = false;
	}

	for (int i = 0; i < 3665; i++)
	{
		notSortWords[i].index = i;
	}
}

void BrowseWords()
{
	loadimage(&browseWords, _T("C:\\Users\\ztlzl\\Desktop\\CE-Dict\\browseWords.jpg"));
	MOUSEMSG m;
	setbkmode(TRANSPARENT);	//�������屳��ɫΪ͸��
	while (1)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			//��������
			if (m.mkLButton == true)
			{
				//��������������ҳ
				if (m.x > 0 && m.x < 95 && m.y > 256 && m.y < 362)
				{
					if (browseIndex == 0)
						browseIndex = 0;
					else
						browseIndex--;
				}
				//�������������ҷ�ҳ
				else if (m.x > 896 && m.x < 995 && m.y > 247 && m.y < 352)
				{
					if (browseIndex == 3665 - 1)
						browseIndex = 3665 - 1;
					else
						browseIndex++;
				}
				//���������˼��뵥�ʱ�
				else if (m.x > 763 && m.x < 871 && m.y > 5 && m.y < 100)
				{
					//word[browseIndex].isInWordsBook = !word[browseIndex].isInWordsBook;
					if (word[browseIndex].isInWordsBook == true)
					{
						word[browseIndex].isInWordsBook = false;
						wordsInWordsBook--;
					}
					else
					{
						word[browseIndex].isInWordsBook = true;
						wordsInWordsBook++;
					}
				}
				//���������˷���
				else if (m.x > 891 && m.x < 995 && m.y > 4 && m.y < 101)
				{
					isReturnBrowseWords = 1;
					break;
				}
				//���������˲�ѯ��ť
				else if (m.x > 235 && m.x < 276 && m.y > 22 && m.y < 66)
				{
					browseIndex = browseSearchNum;
				}
				//����������ɾ����ť
				else if (m.x > 303 && m.x < 351 && m.y > 23 && m.y < 62)
				{
					browseSearchNum /= 10;
				}
			}
		}
		//����м�����Ϣ
		if (_kbhit())
		{
			char ch = _getch();
			if (ch >= '0' && ch <= '9')
			{
				browseSearchNum = browseSearchNum * 10 + (ch - '0');
				if (browseSearchNum >= 3665)
					browseSearchNum = 3664;
			}
			else if (ch == 13)
				//ʶ�𵽻س���
			{
				browseIndex = browseSearchNum;
			}
			else if (ch == 8)
				//ʶ���˸��
			{
				browseSearchNum /= 10;
			}
		}
		drawBrowseWords();
		FlushBatchDraw();
	}
}

void drawBrowseWords()
{
	CHAR chinese[40];
	CHAR english[15];
	CHAR isInWordsBOOK[21];
	CHAR searchNum[10];
	putimage(0, 0, &browseWords);

	if (word[browseIndex].isInWordsBook == true)
		wsprintf(isInWordsBOOK, "%s", "�õ����Ѿ����뵥�ʱ�");
	else
		wsprintf(isInWordsBOOK, "%s", "�õ���δ���뵥�ʱ�");

	wsprintf(chinese, "%s", word[browseIndex].Chinese);
	wsprintf(english, "%s", word[browseIndex].English);

	if(browseSearchNum == 0)
		wsprintf(searchNum, "%s", " ");
	else
		wsprintf(searchNum, "%d", browseSearchNum);

	settextstyle(20, 0, _T("����"));
	settextcolor(RED);
	outtextxy(420, 30, isInWordsBOOK);

	settextstyle(80, 0, _T("����"));
	settextcolor(BLACK);
	outtextxy(100, 200, chinese);
	outtextxy(330, 350, english);

	settextstyle(20, 0, _T("����"));
	outtextxy(38, 33, searchNum);
}

void wordsBook()
{
	loadimage(&WordsBook, _T("C:\\Users\\ztlzl\\Desktop\\CE-Dict\\wordsBook.jpg"));
	MOUSEMSG m;
	int tmp;
	bool isNext;
	setbkmode(TRANSPARENT);	//�������屳��ɫΪ͸��

	if (wordsInWordsBook != 0)
	{
		tmp = worldsBookIndex;
		//��tmpȥ��̽���ʱ����е�һ������
		while (word[tmp].isInWordsBook == false && tmp < 3665)
		{
			tmp++;
		}
		if (tmp < 3665)
		{
			worldsBookIndex = tmp;
		}
	}
	
	while (wordsInWordsBook != 0)//���ʱ���Ϊ��
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			//��������
			if (m.mkLButton == true)
			{
				//��������������ҳ
				if (m.x > 0 && m.x < 95 && m.y > 256 && m.y < 362)
				{
					tmp = worldsBookIndex - 1;
					//��tmpȥ��̽���ʱ���ߵ��׻���û�е��ʣ�û�еĻ�����λ�ò���
					while (word[tmp].isInWordsBook == false && tmp >= 0)
					{
						tmp--;
					}
					if (tmp >= 0)
					{
						worldsBookIndex = tmp;
					}
				}
				//�������������ҷ�ҳ
				else if (m.x > 896 && m.x < 995 && m.y > 247 && m.y < 352)
				{
					tmp = worldsBookIndex + 1;
					//��tmpȥ��̽���ʱ��ұߵ��׻���û�е��ʣ�û�еĻ�����λ�ò���
					while (word[tmp].isInWordsBook == false && tmp < 3665)
					{
						tmp++;
					}
					if (tmp < 3665)
					{
						worldsBookIndex = tmp;
					}
				}
				//�����������Ƴ����ʱ�
				else if (m.x > 763 && m.x < 871 && m.y > 5 && m.y < 100)
				{
					wordsInWordsBook--;
					word[worldsBookIndex].isInWordsBook = false;
					//����ǰ�ĵ����Ƴ����ʱ�֮����ʾ��һ������
					isNext = false;//��ʾ�õ��ʺ����ڵ��ʱ����滹��û����һ��
					tmp = worldsBookIndex + 1;
					//��tmpȥ��̽���ʱ��ұߵ��׻���û�е��ʣ�û�еĻ�����λ�ò���
					while (word[tmp].isInWordsBook == false && tmp < 3665)
					{
						tmp++;
					}
					if (tmp < 3665)
					{
						worldsBookIndex = tmp;
						isNext = true;
					}

					if (isNext == false)
						//�����õ��ʺ����ڵ��ʱ�����û����һ����������Ѱ�ҵ��ʱ��е���һ������
					{
						tmp = worldsBookIndex - 1;
						//��tmpȥ��̽���ʱ���ߵ��׻���û�е��ʣ�û�еĻ�����λ�ò���
						while (word[tmp].isInWordsBook == false && tmp >= 0)
						{
							tmp--;
						}
						if (tmp >= 0)
						{
							isNext = true;
							worldsBookIndex = tmp;
						}
					}
				}
				//���������˷���
				else if (m.x > 891 && m.x < 995 && m.y > 4 && m.y < 101)
				{
					isReturnWordsBook = 1;
					break;
				}
			}
		}
		drawWordsBook();
		FlushBatchDraw();
	}

	if (wordsInWordsBook == 0)
		//����ǵ��ʱ�Ϊ��
	{
		loadimage(&EmptyWordsBook, _T("C:\\Users\\ztlzl\\Desktop\\CE-Dict\\emptyWordsBook.jpg"));
		while (1)
		{
			if (MouseHit())
			{
				m = GetMouseMsg();
				//��������
				if (m.mkLButton == true)
				{
					//�����������˷���
					if (m.x > 891 && m.x < 995 && m.y > 4 && m.y < 101)
					{
						isReturnWordsBook = 1;
						break;
					}
				}
			}
			drawEmptyWordsBook();
			FlushBatchDraw();
		}
	}
}

void drawWordsBook()
{
	CHAR chinese[40];
	CHAR english[15];
	putimage(0, 0, &WordsBook);

	wsprintf(chinese, "%s", word[worldsBookIndex].Chinese);
	wsprintf(english, "%s", word[worldsBookIndex].English);

	settextstyle(80, 0, _T("����"));
	settextcolor(BLACK);
	outtextxy(100, 200, chinese);
	outtextxy(330, 350, english);
}

void drawEmptyWordsBook()
{
	putimage(0, 0, &EmptyWordsBook);
}

void reciteWords()
{
	loadimage(&ReciteChinese, _T("C:\\Users\\ztlzl\\Desktop\\CE-Dict\\reciteChinese.jpg"));
	loadimage(&ReciteEnglish, _T("C:\\Users\\ztlzl\\Desktop\\CE-Dict\\reciteEnglish.jpg"));
	sortMistakeNumOfWords();//��ǰ�浥�ʵ������������
	while (1)
	{
		if (modeOfReciteWords == 0)
			//������
		{
			reciteChinese();
			//���������˷���
			if (isReturnReciteWords == 1)
				break;
		}
		else
			//��Ӣ��
		{
			reciteEnglish();
			//���������˷���
			if (isReturnReciteWords == 1)
				break;
		}
	}
}

void reciteChinese()
{
	putimage(0, 0, &ReciteChinese);
	setbkmode(TRANSPARENT);	//�������屳��ɫΪ͸��
	MOUSEMSG m;
	while (1)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			//��������������
			if (m.mkLButton == true)
			{
				//���������˱�����
				if (m.x > 5 && m.x < 178 && m.y > 5 && m.y < 130)
				{
					modeOfReciteWords = 0;
				}
				//���������˱�Ӣ��
				else if (m.x > 7 && m.x < 167 && m.y > 145 && m.y < 270)
				{
					modeOfReciteWords = 1;
					break;
				}
				//���������˷���
				else if (m.x > 877 && m.x < 994 && m.y > 1 && m.y < 112)
				{
					isReturnReciteWords = 1;
					userAnswer = -1;
					isNextOrLast = true;
					break;
				}
				//����������last
				else if (m.x > 12 && m.x < 129 && m.y > 532 && m.y < 588)
				{
					reciteWordIndex--;
					if (reciteWordIndex < 0)
						reciteWordIndex = 0;
					else
					{
						isNextOrLast = true;
						userAnswer = -1;
					}
				}
				//����������next
				else if (m.x > 847 && m.x < 949 && m.y > 539 && m.y < 595)
				{
					reciteWordIndex++;
					if (reciteWordIndex >= 3665)
						reciteWordIndex = 3664;
					else
					{
						isNextOrLast = true;
						userAnswer = -1;
					}
				}
				//���������˼��뵥�ʱ�
				else if (m.x > 761 && m.x < 875 && m.y > 3 && m.y < 114)
				{
					if (word[reciteWordIndex].isInWordsBook == false)
						word[reciteWordIndex].isInWordsBook = true;
					wordsInWordsBook++;
				}
				//����������ѡ��A
				else if (m.x > 322 && m.x < 400 && m.y > 185 && m.y < 256)
				{
					userAnswer = 0;
				}
				//����������ѡ��B
				else if (m.x > 323 && m.x < 390 && m.y > 274 && m.y < 348)
				{
					userAnswer = 1;
				}
				//����������ѡ��C
				else if (m.x > 326 && m.x < 399 && m.y > 375 && m.y < 436)
				{
					userAnswer = 2;
				}
				//����������ѡ��D
				else if (m.x > 321 && m.x < 403 && m.y > 466 && m.y < 529)
				{
					userAnswer = 3;
				}
			}
		}

		//����м�����Ϣ
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == 'a' || ch == 'A')
			{
				userAnswer = 0;
			}
			else if (ch == 'b' || ch == 'B')
			{
				userAnswer = 1;
			}
			else if (ch == 'c' || ch == 'C')
			{
				userAnswer = 2;
			}
			else if (ch == 'd' || ch == 'D')
			{
				userAnswer = 3;
			}
		}

		drawReciteChinese();
		FlushBatchDraw();
	}
}

void drawReciteChinese()
{
	srand((unsigned)time(NULL));
	CHAR WORD[15];
	putimage(0, 0, &ReciteChinese);

	if (isNextOrLast == true)
	{
		answer = rand() % 4;//��ǰ�Ĵ𰸷����ĸ�ѡ�����棬�������
		int num;
		int optionsNum[4];

		//���ĸ�ѡ��������ϲ��Ƿǵ�ǰ����ѡ���ֵ,�������ĸ�ֵ�����
		do
		{
			do
			{
				num = rand() % 3665;
			} while (num == reciteWordIndex);
			wsprintf(A, "%s", word[num].Chinese);
			optionsNum[0] = num;
			do
			{
				num = rand() % 3665;
			} while (num == reciteWordIndex);
			wsprintf(B, "%s", word[num].Chinese);
			optionsNum[1] = num;
			do
			{
				num = rand() % 3665;
			} while (num == reciteWordIndex);
			wsprintf(C, "%s", word[num].Chinese);
			optionsNum[2] = num;
			do
			{
				num = rand() % 3665;
			} while (num == reciteWordIndex);
			wsprintf(D, "%s", word[num].Chinese);
			optionsNum[3] = num;
		} while (fourNumIsNotEqual(optionsNum) == false);

		//��ȷ�����ĸ�ѡ����������ɺ�ʼ��ֵ
		switch (answer)
		{
		case 0:wsprintf(A, "%s", word[reciteWordIndex].Chinese);
			break;
		case 1:wsprintf(B, "%s", word[reciteWordIndex].Chinese);
			break;
		case 2:wsprintf(C, "%s", word[reciteWordIndex].Chinese);
			break;
		case 3:wsprintf(D, "%s", word[reciteWordIndex].Chinese);
			break;
		}

		isNextOrLast = false;
	}

	wsprintf(WORD, "%s", word[reciteWordIndex].English);

	settextstyle(30, 0, _T("����"));
	settextcolor(BLACK);
	outtextxy(431, 196, A);
	outtextxy(420, 290, B);
	outtextxy(418, 387, C);
	outtextxy(420, 478, D);
	settextstyle(60, 0, _T("����"));
	settextcolor(RED);
	outtextxy(374, 85, WORD);

	CHAR tips[30];
	if (userAnswer == -1)
		//�û���δ��������
	{
		wsprintf(tips, "%s", "������Ļ���ü�������");
	}
	else if (userAnswer == answer)
	{
		wsprintf(tips, "%s", "������ȷ");
	}
	else
	{
		wsprintf(tips, "%s", "�������");
	}

	settextstyle(30, 0, _T("����"));
	settextcolor(GREEN);
	outtextxy(320, 25, tips);
}

void reciteEnglish()
{
	putimage(0, 0, &ReciteEnglish);
	FlushBatchDraw();
	setbkmode(TRANSPARENT);	//�������屳��ɫΪ͸��
	MOUSEMSG m;
	while (1)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			//��������
			if (m.mkLButton == true)
			{
				//���������˼��뵥�ʱ�
				if (m.x > 726 && m.x < 866 && m.y > 2 && m.y < 131)
				{
					if (word[reciteWordIndex].isInWordsBook == false)
						word[reciteWordIndex].isInWordsBook = true;
					wordsInWordsBook++;
				}
				//���������˷���
				else if (m.x > 871 && m.x < 995 && m.y > 1 && m.y < 128)
				{
					isReturnReciteWords = 1;
					numOfLetterInReciteWords = 0;
					userAnswer = -1;
					break;
				}
				//����������LAST
				else if (m.x > 18 && m.x < 150 && m.y > 533 && m.y < 590)
				{
					reciteWordIndex--;
					if (reciteWordIndex < 0)
						reciteWordIndex = 0;
					else
					{
						userWord[0] = '\0';
						isSubmit == false;
						numOfLetterInReciteWords = 0;
						userAnswer = -1;
					}
				}
				//����������NEXT
				else if (m.x > 822 && m.x < 988 && m.y > 535 && m.y < 588)
				{
					reciteWordIndex++;
					if (reciteWordIndex >= 3665)
						reciteWordIndex = 3664;
					else
					{
						userWord[0] = '\0';
						isSubmit == false;
						numOfLetterInReciteWords = 0;
						userAnswer = -1;
					}
				}
				//���������˱�����
				else if (m.x > 5 && m.x < 201 && m.y > 5 && m.y < 138)
				{
					modeOfReciteWords = 0;
					break;
				}
				//���������˱�Ӣ��
				else if (m.x > 4 && m.x < 191 && m.y > 153 && m.y < 302)
				{
					modeOfReciteWords = 1;
				}
				//���������˻س�
				else if ((m.x > 861 && m.x < 937 && m.y > 289 && m.y < 427) || 
					(m.x > 802 && m.x < 855 && m.y > 348 && m.y < 425))
				{
					isSubmit = true;
					userWord[numOfLetterInReciteWords] = '\0';
					if ((strcmp(word[reciteWordIndex].English, userWord)) == 0)
					{
						userAnswer = 1;//����������ȷ
					}
					else
					{
						userAnswer = 2;//�����������
					}
				}
				//����������ɾ��
				else if (m.x > 815 && m.x < 922 && m.y > 439 && m.y < 501)
				{
					if (numOfLetterInReciteWords == 0)
						userWord[0] = '\0';
					else if (numOfLetterInReciteWords > 0)
					{
						userWord[numOfLetterInReciteWords - 1] = '\0';
						numOfLetterInReciteWords--;
					}
				}
			}
		}

		//����м�����Ϣ
		if (_kbhit())
		{
			char ch = _getch();
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
				//�������ĸ
			{
				if (ch >= 'a' && ch <= 'z')
					//�����Сд
				{
					userWord[numOfLetterInReciteWords] = ch;
				}
				else
					//����Ǵ�д
				{
					userWord[numOfLetterInReciteWords] = ch + 32;
				}
				numOfLetterInReciteWords++;
			}
			else if (ch == 8)
				//ɾ�������˸�
			{
				if(numOfLetterInReciteWords == 0)
					userWord[0] = '\0';
				else if (numOfLetterInReciteWords > 0)
				{
					userWord[numOfLetterInReciteWords - 1] = '\0';
					numOfLetterInReciteWords--;
				}
			}
			else if (ch == 13)
				//�س���
			{
				isSubmit = true;
				userWord[numOfLetterInReciteWords] = '\0';
				if ((strcmp(word[reciteWordIndex].English, userWord)) == 0)
				{
					userAnswer = 1;//����������ȷ
				}
				else
				{
					userAnswer = 2;//�����������
				}
			}
		}

		drawReciteEnglish();
		FlushBatchDraw();
	}
}

void drawReciteEnglish()
{
	CHAR CHINESE[40];
	CHAR tips[30];
	
	if (isSubmit == false)
	{
		wsprintf(tips, "%s", "�����뵥�ʲ����س�");
	}
	else
	{
		if (userAnswer == 1)
		{
			wsprintf(tips, "%s", "������ȷ");
		}
		else
		{
			wsprintf(tips, "%s", "�������");
		}
	}

	wsprintf(CHINESE, "%s", word[reciteWordIndex].Chinese);

	putimage(0, 0, &ReciteEnglish);
	settextstyle(30, 0, _T("����"));
	settextcolor(GREEN);
	outtextxy(320, 25, tips);
	settextstyle(60, 0, _T("����"));
	settextcolor(RED);
	outtextxy(375, 182, CHINESE);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("����"));
	userWord[numOfLetterInReciteWords] = '\0';
	outtextxy(360, 370, userWord);
}

void testWordsInit()
{
	loadimage(&testWords, _T("C:\\Users\\ztlzl\\Desktop\\CE-Dict\\testInit.jpg"));
	MOUSEMSG m;
	while (1)
	{
		putimage(0, 0, &testWords);
		FlushBatchDraw();
		if (MouseHit())
		{
			m = GetMouseMsg();
			//��������
			if (m.mkLButton == true)
			{
				//�������������Ĳ���
				if (m.x > 280 && m.x < 583 && m.y > 118 && m.y < 205)
				{
					beginTime = time(NULL);
					testWordsChilese();
				}
				//����������Ӣ�Ĳ���
				else if (m.x > 271 && m.x < 576 && m.y > 252 && m.y < 329)
				{
					beginTime = time(NULL);
					testWordsEnglish();
				}
				//���������˷���
				else if (m.x > 905 && m.x < 995 && m.y > 5 && m.y < 92)
				{
					isReturnTestWords = 1;
					break;
				}
			}
		}
	}
}

bool tenNumIsNotEqual(int *a)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = i + 1; j < 10; j++)
		{
			if (a[i] == a[j])
				return false;
		}
	}
	return true;
}

bool fourNumIsNotEqual(int *a)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			if (a[i] == a[j])
				return false;
		}
	}
	return true;
}

void testWordsChilese()
{
	srand((unsigned)time(NULL));
	//��ʼ������
	isSubmitInTestChinese = 0;
	testWordChinese = 0;//��ǰ���ʲ�����ʾ�ڼ������ʵ��±�
	isTextedInTestChinese = 0;//��ǰ���ʲ����Ѿ������˼�������
	loadimage(&testWordsChileseIMG, _T("C:\\Users\\ztlzl\\Desktop\\CE-Dict\\testWordsChilese.jpg"));
	int wordsNum[10];//��������Ŀ������
	int optionsNum[4];//�������ĸ�ѡ�������

	//���ɲ�ͬ��10����Ŀ
	do
	{
		for (int i = 0; i < 10; i++)
		{
			wordsNum[i] = rand() % 3665;
		}
	} while (tenNumIsNotEqual(wordsNum) == false);//�����ɵ���Ŀ���ظ���ʱ�򣬾ͼ�������

	//����ʮ����ͬ��Ŀ��ѡ��
	for (int i = 0; i < 10; i++)
	{
		chineseExercise[i].index = wordsNum[i];
		//��ǰ�Ĵ𰸷����ĸ�ѡ�����棬�������. 1 2 3 4��ʾA B C D
		chineseExercise[i].trueAnswer = (rand() % 4) + 1;
		chineseExercise[i].userAnswer = 0;
		
		//��do-whileȷ���ĸ�ѡ���ǲ���ȵ�
		do
		{
			//���ĸ�ѡ��������ϲ��Ƿǵ�ǰ����ѡ���ֵ
			do
			{
				chineseExercise[i].a = rand() % 3665;
			} while (chineseExercise[i].a == chineseExercise[i].index);
			do
			{
				chineseExercise[i].b = rand() % 3665;
			} while (chineseExercise[i].b == chineseExercise[i].index);
			do
			{
				chineseExercise[i].c = rand() % 3665;
			} while (chineseExercise[i].c == chineseExercise[i].index);
			do
			{
				chineseExercise[i].d = rand() % 3665;
			} while (chineseExercise[i].d == chineseExercise[i].index);

			optionsNum[0] = chineseExercise[i].a;
			optionsNum[1] = chineseExercise[i].b;
			optionsNum[2] = chineseExercise[i].c;
			optionsNum[3] = chineseExercise[i].d;
		} while (fourNumIsNotEqual(optionsNum) == false);

		//��ȷ�����ĸ�ѡ����������ɺ�ʼ��ֵ
		switch (chineseExercise[i].trueAnswer)
		{
		case 1:chineseExercise[i].a = chineseExercise[i].index;
			break;
		case 2:chineseExercise[i].b = chineseExercise[i].index;
			break;
		case 3:chineseExercise[i].c = chineseExercise[i].index;
			break;
		case 4:chineseExercise[i].d = chineseExercise[i].index;
			break;
		}
	}
	MOUSEMSG m;
	while (1)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			//��������
			if (m.mkLButton == true)
			{
				//����������ѡ��A
				if (m.x > 325 && m.x < 403 && m.y > 213 && m.y < 265)
				{
					if (chineseExercise[testWordChinese].userAnswer == 0)
						isTextedInTestChinese++;
					chineseExercise[testWordChinese].userAnswer = 1;
				}
				//����������ѡ��B
				else if (m.x > 321 && m.x < 393 && m.y > 296 && m.y < 348)
				{
					if (chineseExercise[testWordChinese].userAnswer == 0)
						isTextedInTestChinese++;
					chineseExercise[testWordChinese].userAnswer = 2;
				}
				//����������ѡ��C
				else if (m.x > 324 && m.x < 392 && m.y > 389 && m.y < 449)
				{
					if (chineseExercise[testWordChinese].userAnswer == 0)
						isTextedInTestChinese++;
					chineseExercise[testWordChinese].userAnswer = 3;
				}
				//����������ѡ��D
				else if (m.x > 323 && m.x < 392 && m.y > 475 && m.y < 535)
				{
					if (chineseExercise[testWordChinese].userAnswer == 0)
						isTextedInTestChinese++;
					chineseExercise[testWordChinese].userAnswer = 4;
				}
				//����������ѡ��LAST
				else if (m.x > 9 && m.x < 140 && m.y > 539 && m.y < 592)
				{
					testWordChinese--;
					if (testWordChinese < 0)
						testWordChinese = 0;
				}
				//����������ѡ��NEXT
				else if (m.x > 855 && m.x < 990 && m.y > 546 && m.y < 592)
				{
					testWordChinese++;
					if (testWordChinese >= 9)
						testWordChinese = 9;
				}
				//����������ѡ���ύ
				else if (m.x > 680 && m.x < 863 && m.y > 1 && m.y < 50)
				{
					trueNumInTestChinese = 0;
					isSubmitInTestChinese = 1;
					for (int i = 0; i < 10; i++)
					{
						if (chineseExercise[i].userAnswer == chineseExercise[i].trueAnswer)
						{
							trueNumInTestChinese++;
						}
					}
				}
				//����������ѡ���
				else if (m.x > 873 && m.x < 993 && m.y > 5 && m.y < 123)
				{
					break;
				}
			}
		}

		//����м�����Ϣ
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == 'a' || ch == 'A')
			{
				if (chineseExercise[testWordChinese].userAnswer == 0)
					isTextedInTestChinese++;
				chineseExercise[testWordChinese].userAnswer = 1;
			}
			else if (ch == 'b' || ch == 'B')
			{
				if (chineseExercise[testWordChinese].userAnswer == 0)
					isTextedInTestChinese++;
				chineseExercise[testWordChinese].userAnswer = 2;
			}
			else if (ch == 'c' || ch == 'C')
			{
				if (chineseExercise[testWordChinese].userAnswer == 0)
					isTextedInTestChinese++;
				chineseExercise[testWordChinese].userAnswer = 3;
			}
			else if (ch == 'd' || ch == 'D')
			{
				if (chineseExercise[testWordChinese].userAnswer == 0)
					isTextedInTestChinese++;
				chineseExercise[testWordChinese].userAnswer = 4;
			}
			else if (ch == 13)
				//�������»س�������ʾ�ύ
			{
				trueNumInTestChinese = 0;
				isSubmitInTestChinese = 1;
				for (int i = 0; i < 10; i++)
				{
					if (chineseExercise[testWordChinese].userAnswer == chineseExercise[testWordChinese].trueAnswer)
					{
						trueNumInTestChinese++;
					}
				}
			}
		}

		drawTestWordsChilese();
		FlushBatchDraw();
	}
}

void drawTestWordsChilese()
{
	setbkmode(TRANSPARENT);	//�������屳��ɫΪ͸��
	putimage(0, 0, &testWordsChileseIMG);
	wsprintf(A, "%s", word[chineseExercise[testWordChinese].a].Chinese);
	wsprintf(B, "%s", word[chineseExercise[testWordChinese].b].Chinese);
	wsprintf(C, "%s", word[chineseExercise[testWordChinese].c].Chinese);
	wsprintf(D, "%s", word[chineseExercise[testWordChinese].d].Chinese);

	switch (chineseExercise[testWordChinese].trueAnswer)
	{
	case 1:wsprintf(A, "%s", word[chineseExercise[testWordChinese].index].Chinese);
		break;
	case 2:wsprintf(B, "%s", word[chineseExercise[testWordChinese].index].Chinese);
		break;
	case 3:wsprintf(C, "%s", word[chineseExercise[testWordChinese].index].Chinese);
		break;
	case 4:wsprintf(D, "%s", word[chineseExercise[testWordChinese].index].Chinese);
		break;
	}

	CHAR wordsInTestChinese[20];
	wsprintf(wordsInTestChinese, "%s", word[chineseExercise[testWordChinese].index].English);

	settextstyle(30, 0, _T("����"));
	settextcolor(BLACK);
	outtextxy(395, 223, A);
	outtextxy(391, 306, B);
	outtextxy(394, 399, C);
	outtextxy(393, 485, D);
	settextstyle(60, 0, _T("����"));
	settextcolor(RED);
	outtextxy(340, 112, wordsInTestChinese);

	CHAR tips[30];
	if (chineseExercise[testWordChinese].userAnswer == 0)
		//�û���δ����
	{
		if (isSubmitInTestChinese == 0)
			//�����û�е���ύ
		{
			wsprintf(tips, "%s", "���ü��̻������������");
		}
		wsprintf(tips, "%s", "��һ����û���ύ��");
	}
	else if (chineseExercise[testWordChinese].userAnswer == 1)
	{
		wsprintf(tips, "%s", "��ѡ��Ĵ��ǣ�A");
	}
	else if (chineseExercise[testWordChinese].userAnswer == 2)
	{
		wsprintf(tips, "%s", "��ѡ��Ĵ��ǣ�B");
	}
	else if (chineseExercise[testWordChinese].userAnswer == 3)
	{
		wsprintf(tips, "%s", "��ѡ��Ĵ��ǣ�C");
	}
	else if (chineseExercise[testWordChinese].userAnswer == 4)
	{
		wsprintf(tips, "%s", "��ѡ��Ĵ��ǣ�D");
	}
	
	settextstyle(20, 0, _T("����"));
	settextcolor(GREEN);
	outtextxy(332, 9, tips);

	CHAR remainTest[32];//��ʾ�û����м�����Ŀû������
	if (isSubmitInTestChinese == 0)
		//�����û�е���ύ
	{
		if (isTextedInTestChinese == 0)
		{
			wsprintf(remainTest, "%s", "����10��û������");
		}
		else if (isTextedInTestChinese == 1)
		{
			wsprintf(remainTest, "%s", "����9��û������");
		}
		else if (isTextedInTestChinese == 2)
		{
			wsprintf(remainTest, "%s", "����8��û������");
		}
		else if (isTextedInTestChinese == 3)
		{
			wsprintf(remainTest, "%s", "����7��û������");
		}
		else if (isTextedInTestChinese == 4)
		{
			wsprintf(remainTest, "%s", "����6��û������");
		}
		else if (isTextedInTestChinese == 5)
		{
			wsprintf(remainTest, "%s", "����5��û������");
		}
		else if (isTextedInTestChinese == 6)
		{
			wsprintf(remainTest, "%s", "����4��û������");
		}
		else if (isTextedInTestChinese == 7)
		{
			wsprintf(remainTest, "%s", "����3��û������");
		}
		else if (isTextedInTestChinese == 8)
		{
			wsprintf(remainTest, "%s", "����2��û������");
		}
		else if (isTextedInTestChinese == 9)
		{
			wsprintf(remainTest, "%s", "����1��û������");
		}
		else if (isTextedInTestChinese == 10)
		{
			wsprintf(remainTest, "%s", "������ϣ�ȷ������������ύ");
		}
	}
	else
		//�Ѿ��ύ��
	{
		settextcolor(RED);
		if (chineseExercise[testWordChinese].userAnswer == chineseExercise[testWordChinese].trueAnswer)
			//�������������ȷ
		{
			wsprintf(remainTest, "%s", "������ȷ");
		}
		else
		{
			wsprintf(remainTest, "%s", "�������");
		}
	}
	outtextxy(331, 39, remainTest);

	CHAR trueAnswer[32];//�û�����ύ������𰸴�������ʾ��ȷ�𰸣���ȷ����ʾ��ϲ��
	if (isSubmitInTestChinese == 0)
		//�����û�е���ύ
	{
		wsprintf(trueAnswer, "%s", "");
	}
	else
	{
		if (chineseExercise[testWordChinese].userAnswer == chineseExercise[testWordChinese].trueAnswer)
			//�������������ȷ
		{
			wsprintf(trueAnswer, "%s", "��ϲ��");
		}
		else
		{
			switch (chineseExercise[testWordChinese].trueAnswer)
			{
			case 1:wsprintf(trueAnswer, "%s", "��ȷ��ΪA");
				break;
			case 2:wsprintf(trueAnswer, "%s", "��ȷ��ΪB");
				break;
			case 3:wsprintf(trueAnswer, "%s", "��ȷ��ΪC");
				break;
			case 4:wsprintf(trueAnswer, "%s", "��ȷ��ΪD");
				break;
			}
		}
	}
	settextcolor(GREEN);
	outtextxy(331, 69, trueAnswer);

	if (isSubmitInTestChinese == 1)
	{
		CHAR score[2];
		settextcolor(RED);
		wsprintf(score, "%d", trueNumInTestChinese);
		outtextxy(10, 110, _T("�÷֣�"));
		outtextxy(70, 110, score);
	}

	settextstyle(40, 0, _T("����"));
	if (isSubmitInTestChinese == 0)
	{
		nowTime = time(NULL);
	}
	CHAR times[10];
	wsprintf(times, "%ld", (nowTime - beginTime));
	outtextxy(110, 60, times);
}

void testWordsEnglish()
{
	isTextedInTestEnglish = 0;
	testWordEnglish = 0;
	isSubmitInTestEnglish = 0;
	srand((unsigned)time(NULL));
	loadimage(&testWordsEnglishIMG, _T("C:\\Users\\ztlzl\\Desktop\\CE-Dict\\testWordsEnglish.jpg"));

	int indexNum[10];
	//����ʮ����ͬ�ĵ���������������Ŀ
	do
	{
		for (int i = 0; i < 10; i++)
		{
			indexNum[i] = rand() % 3665;
		}
	} while (tenNumIsNotEqual(indexNum) == false);

	//���ṹ�������index��ֵ��������Ҫ�ĳ�ʼ��
	for (int i = 0; i < 10; i++)
	{
		englishExercise[i].index = indexNum[i];
		englishExercise[i].nextLetterIndex = 0;
		englishExercise[i].userAnswer[0] = '\0';
	}

	MOUSEMSG m;
	while (1)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			//��������
			if (m.mkLButton == true)
			{
				//����������submit
				if (m.x > 734 && m.x < 878 && m.y > 5 && m.y < 44)
				{
					trueNumInTestEnglish = 0;
					isSubmitInTestEnglish = 1;
					for (int i = 0; i < 10; i++)
					{
						if (strcmp(englishExercise[i].userAnswer, word[englishExercise[i].index].English) == 0)
						{
							trueNumInTestEnglish++;
						}
					}
				}
				//�����������˳�
				else if (m.x > 888 && m.x < 996 && m.y > 4 && m.y < 110)
				{
					break;
				}
				//����������LAST
				else if (m.x > 9 && m.x < 133 && m.y > 543 && m.y < 591)
				{
					testWordEnglish--;
					if (testWordEnglish < 0)
						testWordEnglish = 0;
				}
				//����������NEXT
				else if (m.x > 846 && m.x < 998 && m.y > 543 && m.y < 599)
				{
					testWordEnglish++;
					if (testWordEnglish >= 9)
						testWordEnglish = 9;
				}	
				//����������ɾ����
				else if (m.x > 817 && m.x < 930 && m.y > 368 && m.y < 437)
				{
					englishExercise[testWordEnglish].nextLetterIndex--;
					if (englishExercise[testWordEnglish].nextLetterIndex < 0)
						englishExercise[testWordEnglish].nextLetterIndex = 0;
					//ȷ���ַ�����\0����
					englishExercise[testWordEnglish].userAnswer[englishExercise[testWordEnglish].nextLetterIndex] = '\0';
				}
			}
		}

		//����м�����Ϣ
		if (_kbhit())
		{
			char ch = _getch();
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
			{
				if (ch >= 'a' && ch <= 'z')
					//�����Сд
				{
					englishExercise[testWordEnglish].userAnswer[englishExercise[testWordEnglish].nextLetterIndex] = ch;
				}
				else
					//����Ǵ�д
				{
					englishExercise[testWordEnglish].userAnswer[englishExercise[testWordEnglish].nextLetterIndex] = ch + 32;
				}
				englishExercise[testWordEnglish].nextLetterIndex++;
				//ȷ���ַ�����\0����
				englishExercise[testWordEnglish].userAnswer[englishExercise[testWordEnglish].nextLetterIndex] = '\0';
			}
			else if (ch == 8)
				//�˸�
			{
				englishExercise[testWordEnglish].nextLetterIndex--;
				if (englishExercise[testWordEnglish].nextLetterIndex < 0)
					englishExercise[testWordEnglish].nextLetterIndex = 0;
				//ȷ���ַ�����\0����
				englishExercise[testWordEnglish].userAnswer[englishExercise[testWordEnglish].nextLetterIndex] = '\0';
			}
			else if (ch == 8)
				//�س�
			{
				trueNumInTestEnglish = 0;
				isSubmitInTestEnglish = 1;
				for (int i = 0; i < 10; i++)
				{
					if (strcmp(englishExercise[i].userAnswer, word[englishExercise[i].index].English) == 0)
					{
						trueNumInTestChinese++;
					}
				}
			}
		}

		drawTestWordsEnglish();
		FlushBatchDraw();
	}
}

void drawTestWordsEnglish()
{
	setbkmode(TRANSPARENT);	//�������屳��ɫΪ͸��
	putimage(0, 0, &testWordsEnglishIMG);

	settextstyle(20, 0, _T("����"));
	settextcolor(GREEN);
	CHAR tips[30];
	if (englishExercise[testWordEnglish].nextLetterIndex == 0)
		//�û���Ϊ��
	{
		wsprintf(tips, "%s", "��Ӽ��̼����");
	}
	else
	{
		wsprintf(tips, "%s", englishExercise[testWordEnglish].userAnswer);
		outtextxy(332, 9, _T("���Ĵ��ǣ�"));
	}
	if (englishExercise[testWordEnglish].nextLetterIndex == 0 &&
		isSubmitInTestEnglish == 1)
	{
		wsprintf(tips, "%s", "����δ����");
	}
	if (englishExercise[testWordEnglish].nextLetterIndex == 0)
		//�û���Ϊ��
	{
		outtextxy(332, 9, tips);
	}
	else
	{
		outtextxy(445, 9, tips);
	}


	CHAR wordInBox[30];
	wsprintf(wordInBox, "%s", englishExercise[testWordEnglish].userAnswer);
	settextstyle(60, 0, _T("����"));
	settextcolor(BLACK);
	outtextxy(261, 352, wordInBox);

	CHAR ChineseExercise[40];
	settextstyle(50, 0, _T("����"));
	settextcolor(RED);
	wsprintf(ChineseExercise, "%s", word[englishExercise[testWordEnglish].index].Chinese);
	outtextxy(330, 130, ChineseExercise);

	CHAR remainTest[32];//��ʾ�û����м�����Ŀû������
	settextstyle(20, 0, _T("����"));
	settextcolor(GREEN);
	isTextedInTestEnglish = 0;
	for (int i = 0; i < 10; i++)
	{
		if (englishExercise[i].nextLetterIndex != 0)
		{
			isTextedInTestEnglish++;
		}
	}
	if (isSubmitInTestEnglish == 0)
		//�����û�е���ύ
	{
		if (isTextedInTestEnglish == 0)
		{
			wsprintf(remainTest, "%s", "����10��û������");
		}
		else if (isTextedInTestEnglish == 1)
		{
			wsprintf(remainTest, "%s", "����9��û������");
		}
		else if (isTextedInTestEnglish == 2)
		{
			wsprintf(remainTest, "%s", "����8��û������");
		}
		else if (isTextedInTestEnglish == 3)
		{
			wsprintf(remainTest, "%s", "����7��û������");
		}
		else if (isTextedInTestEnglish == 4)
		{
			wsprintf(remainTest, "%s", "����6��û������");
		}
		else if (isTextedInTestEnglish == 5)
		{
			wsprintf(remainTest, "%s", "����5��û������");
		}
		else if (isTextedInTestEnglish == 6)
		{
			wsprintf(remainTest, "%s", "����4��û������");
		}
		else if (isTextedInTestEnglish == 7)
		{
			wsprintf(remainTest, "%s", "����3��û������");
		}
		else if (isTextedInTestEnglish == 8)
		{
			wsprintf(remainTest, "%s", "����2��û������");
		}
		else if (isTextedInTestEnglish == 9)
		{
			wsprintf(remainTest, "%s", "����1��û������");
		}
		else if (isTextedInTestEnglish == 10)
		{
			wsprintf(remainTest, "%s", "������ϣ�ȷ������������ύ");
		}
	}
	else
		//�Ѿ��ύ��
	{
		settextcolor(RED);
		if (strcmp(englishExercise[testWordEnglish].userAnswer, word[englishExercise[testWordEnglish].index].English) == 0)
			//�������������ȷ
		{
			wsprintf(remainTest, "%s", "������ȷ");
		}
		else
		{
			wsprintf(remainTest, "%s", "�������");
		}
	}
	outtextxy(331, 39, remainTest);

	settextstyle(20, 0, _T("����"));
	settextcolor(GREEN);
	if (isSubmitInTestEnglish == 1)
		//����Ѿ�����ύ��
	{
		if (strcmp(englishExercise[testWordEnglish].userAnswer, word[englishExercise[testWordEnglish].index].English) == 0)
			//�������������ȷ
		{
			CHAR trueAnswer[15];
			wsprintf(trueAnswer, "%s", "��ϲ��");
			outtextxy(331, 69, trueAnswer);
		}
		else
		{
			CHAR trueAnswer[15];
			wsprintf(trueAnswer, "%s", word[englishExercise[testWordEnglish].index].English);
			outtextxy(331, 69, "��ȷ�𰸣�");
			outtextxy(430, 69, trueAnswer);
		}
	}

	if (isSubmitInTestEnglish == 0)
	{
		nowTime = time(NULL);
	}
	CHAR times[10];
	wsprintf(times, "%ld", (nowTime - beginTime));
	settextstyle(30, 0, _T("����"));
	outtextxy(115, 55, times);

	if (isSubmitInTestEnglish == 1)
	{
		CHAR score[2];
		settextcolor(RED);
		wsprintf(score, "%d", trueNumInTestEnglish);
		outtextxy(10, 110, _T("�÷֣�"));
		outtextxy(90, 110, score);
	}
}

void loadWordTxt()
{
	readWord();//���ú������ļ��ж�ȡ���ʴ���ṹ������
	writeWord();//���ú����ѽṹ������������Զ����Ƶ���ʽ��ŵ��ļ���
}

void loadHistoryData()
{
	FILE *fp;
	if ((fp = fopen("C:\\Users\\ztlzl\\Desktop\\cet4Date.txt", "r")) == NULL)
		//���ı�
	{
		printf("Can not open the file!");
		exit(0);
	}
	/*
	�����µ��������ݶ���
	browseIndex //��������Ľṹ�������±�
	modeOfReciteWords //�����ʵ�ģʽ��0Ϊ�����ģ�1Ϊ��Ӣ�ģ�Ĭ��Ϊ0
	reciteWordIndex //��ǰ���еĵ��ʵ��±꣬Ĭ��Ϊ0
	*/
	fscanf(fp, "%d %d %d", &browseIndex, &modeOfReciteWords, &reciteWordIndex);
	fclose(fp);
}

void saveThisData()
{
	FILE *fp;
	if ((fp = fopen("C:\\Users\\ztlzl\\Desktop\\cet4Date.txt", "w")) == NULL) 
		//д�ı�
	{
		printf("Can not open the file!");
		exit(0);
	}
	char s[5];
	/*
	�����µ��������ݷֱ�����ļ���ÿһ���Ѵﵽ������ȵ�Ч�� 
	browseIndex //��������Ľṹ�������±�
	modeOfReciteWords //�����ʵ�ģʽ��0Ϊ�����ģ�1Ϊ��Ӣ�ģ�Ĭ��Ϊ0
	reciteWordIndex //��ǰ���еĵ��ʵ��±꣬Ĭ��Ϊ0
	*/
	fputs(itoa(browseIndex, s, 10), fp);
	fputs("\n", fp);
	fputs(itoa(modeOfReciteWords, s, 10), fp);
	fputs("\n", fp);
	fputs(itoa(reciteWordIndex, s, 10), fp);
	fclose(fp);
}

void sortMistakeNumOfWords()
{
	for (int i = 0; i < 3665; i++)
	{
		sortedWords[i].errorTimes = notSortWords[i].errorTimes;
		sortedWords[i].index = notSortWords[i].index;
	}

	qsort(sortedWords, 3665, sizeof(sortedWords[0]), comp);
}

int comp(const void*a, const void*b)
{
	int ret = 0;
	if ((*(mistakeNumOfWords*)a).errorTimes > (*(mistakeNumOfWords*)b).errorTimes)
	{
		ret = -1;
	}
	else if ((*(mistakeNumOfWords*)a).errorTimes < (*(mistakeNumOfWords*)b).errorTimes)
	{
		ret = 1;
	}
	else
	{
		ret = 0;
	}
	return ret;
}

/*
rewind(fp);//ʹ���ļ���дָ��λ�����»ص���ͷ����Ϊ��д���ļ�ʱ�ļ���дָ�����ļ�ĩβ
	Word temp;
	while (fread(&temp, sizeof(Word), 1, fp) == 1)
	{
		printf("%s  %s\n", temp.English, temp.Chinese);
	}
*/

/*
int main()
{
	IMAGE imgMenu;//init����
	setlocale(LC_ALL, "");
	initgraph(1000, 600);
	// ��ȡ���ھ��
	HWND hwnd = GetHWnd();
	//����Ϸ���������ڴ���
	SetWindowText(hwnd, _T("CET4Ӣ���ʵ�"));
	loadimage(&imgMenu, _T("C:\\Users\\ztlzl\\Desktop\\CE-Dict\\testWordsEnglish.jpg"));
	putimage(0, 0, &imgMenu);
	//_getch()
	MOUSEMSG m;
	int i = 0;
	while (i < 8)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			//��������
			if (m.mkLButton == true)
			{
				i++;
				printf("%d %d\n", m.x, m.y);
			}
		}
	}
	return 0;
}
*/