#include "Dictionary.h"

/*
未完成：

1.强化记忆--- 编写强化记忆函数
2.英语查询---英文全查询函数
3.中文查询---尝试一下，可能不在我能力范围之类
*/

int main()
{
	setlocale(LC_ALL, "");
	initgraph(1000, 600);
	// 获取窗口句柄
	HWND hwnd = GetHWnd();
	//把名称设置在窗口
	SetWindowText(hwnd, _T("CET4英汉词典"));
	//批量制图开始
	BeginBatchDraw();
	loadimage(&imgMenu, _T("C:\\Users\\ztlzl\\Desktop\\CE-Dict\\bk.jpg"));
	init();
	readWord();//调用函数从文件中读取单词存入结构体数组
	writeWord();//调用函数把结构体数组的数据以二进制的形式存放到文件中
	MOUSEMSG m;
	loop:putimage(0, 0, &imgMenu);
	FlushBatchDraw();
	while (1)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			//如果鼠标点击
			if (m.mkLButton == true)
			{
				//如果点击到了载入文本文件
				if (m.x > 393 && m.x < 600 && m.y > 27 && m.y < 113)
				{
					loadWordTxt();
				}
				//如果点击到了载入历史数据
				else if (m.x > 393 && m.x < 603 && m.y > 161 && m.y < 256)
				{
					loadHistoryData();
				}
				//如果点击到了此次数据存档
				else if (m.x > 392 && m.x < 604 && m.y > 304 && m.y < 384)
				{
					saveThisData();
				}
				//如果点击到了单词浏览
				else if (m.x > 389 && m.x < 608 && m.y > 427 && m.y < 514)
				{
					BrowseWords();
					if (isReturnBrowseWords == 1)
					{
						isReturnBrowseWords = 0;
						goto loop;
					}
				}
				//如果点击到了单词背诵
				else if (m.x > 670 && m.x < 875 && m.y > 26 && m.y < 107)
				{
					reciteWords();
					if (isReturnReciteWords == 1)
					{
						isReturnReciteWords = 0;
						goto loop;
					}
				}
				//如果点击到了单词测验
				else if (m.x > 672 && m.x < 869 && m.y > 161 && m.y < 251)
				{
					testWordsInit();
					if (isReturnTestWords == 1)
					{
						isReturnTestWords = 0;
						goto loop;
					}
				}
				//如果点击到了单词查询
				else if (m.x > 669 && m.x < 876 && m.y > 304 && m.y < 385)
				{

				}
				//如果点击到了单词本
				else if (m.x > 662 && m.x < 879 && m.y > 428 && m.y < 512)
				{
					wordsBook();
					if (isReturnWordsBook == 1)
					{
						isReturnWordsBook = 0;
						goto loop;
					}
				}
				//如果点击到了EXIT
				else if (m.x > 897 && m.x < 995 && m.y > 8 && m.y < 46)
				{
					MessageBox(GetHWnd(), "     期待您的下次使用", "CET4英汉词典", MB_OK);
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
		//一行一行的读取文件分析并且完成结构体数组的赋值
	{
		i = 0;
		j = 0;
		if ((isalpha(s[0]) != 0) && (isalpha(s[1]) != 0))//该行为单词行
		{
			while (s[i] != 32)//直到读到一行的空格，也就是把单词读完
			{
				(word[wordCnt]).English[j++] = s[i++];
			}
			(word[wordCnt]).English[j] = '\0';//保证字符串以\0结尾
			j = 0;
			while (s[i] != '\n')
				//直到读到一行的末尾，也就是把中文释义读完
			{
				(word[wordCnt]).Chinese[j++] = s[i++];
			}
			(word[wordCnt]).Chinese[j] = '\0';//保证字符串以\0结尾
			wordCnt++;
		}
	}
	fclose(wordFile);
}

void writeWord()
{
	FILE *fp;
	if ((fp = fopen("C:\\Users\\ztlzl\\Desktop\\binaryCet4.txt", "wb+"))
		== NULL) {//读写二进制文本
		printf("Can not open the file!");
		exit(0);
	}
	fwrite(word, sizeof(Word), 3665, fp);
	fclose(fp);
}

void init()
{
	//给每个单词结构体的索引赋初值
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
	setbkmode(TRANSPARENT);	//设置字体背景色为透明
	while (1)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			//如果鼠标点击
			if (m.mkLButton == true)
			{
				//如果点击到了往左翻页
				if (m.x > 0 && m.x < 95 && m.y > 256 && m.y < 362)
				{
					if (browseIndex == 0)
						browseIndex = 0;
					else
						browseIndex--;
				}
				//如果点击到了往右翻页
				else if (m.x > 896 && m.x < 995 && m.y > 247 && m.y < 352)
				{
					if (browseIndex == 3665 - 1)
						browseIndex = 3665 - 1;
					else
						browseIndex++;
				}
				//如果点击到了加入单词本
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
				//如果点击到了返回
				else if (m.x > 891 && m.x < 995 && m.y > 4 && m.y < 101)
				{
					isReturnBrowseWords = 1;
					break;
				}
				//如果点击到了查询按钮
				else if (m.x > 235 && m.x < 276 && m.y > 22 && m.y < 66)
				{
					browseIndex = browseSearchNum;
				}
				//如果点击到了删除按钮
				else if (m.x > 303 && m.x < 351 && m.y > 23 && m.y < 62)
				{
					browseSearchNum /= 10;
				}
			}
		}
		//如果有键盘消息
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
				//识别到回车键
			{
				browseIndex = browseSearchNum;
			}
			else if (ch == 8)
				//识别到退格键
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
		wsprintf(isInWordsBOOK, "%s", "该单词已经加入单词本");
	else
		wsprintf(isInWordsBOOK, "%s", "该单词未加入单词本");

	wsprintf(chinese, "%s", word[browseIndex].Chinese);
	wsprintf(english, "%s", word[browseIndex].English);

	if(browseSearchNum == 0)
		wsprintf(searchNum, "%s", " ");
	else
		wsprintf(searchNum, "%d", browseSearchNum);

	settextstyle(20, 0, _T("宋体"));
	settextcolor(RED);
	outtextxy(420, 30, isInWordsBOOK);

	settextstyle(80, 0, _T("宋体"));
	settextcolor(BLACK);
	outtextxy(100, 200, chinese);
	outtextxy(330, 350, english);

	settextstyle(20, 0, _T("宋体"));
	outtextxy(38, 33, searchNum);
}

void wordsBook()
{
	loadimage(&WordsBook, _T("C:\\Users\\ztlzl\\Desktop\\CE-Dict\\wordsBook.jpg"));
	MOUSEMSG m;
	int tmp;
	bool isNext;
	setbkmode(TRANSPARENT);	//设置字体背景色为透明

	if (wordsInWordsBook != 0)
	{
		tmp = worldsBookIndex;
		//用tmp去试探单词本当中第一个单词
		while (word[tmp].isInWordsBook == false && tmp < 3665)
		{
			tmp++;
		}
		if (tmp < 3665)
		{
			worldsBookIndex = tmp;
		}
	}
	
	while (wordsInWordsBook != 0)//单词本不为空
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			//如果鼠标点击
			if (m.mkLButton == true)
			{
				//如果点击到了往左翻页
				if (m.x > 0 && m.x < 95 && m.y > 256 && m.y < 362)
				{
					tmp = worldsBookIndex - 1;
					//用tmp去试探单词本左边到底还有没有单词，没有的话保持位置不变
					while (word[tmp].isInWordsBook == false && tmp >= 0)
					{
						tmp--;
					}
					if (tmp >= 0)
					{
						worldsBookIndex = tmp;
					}
				}
				//如果点击到了往右翻页
				else if (m.x > 896 && m.x < 995 && m.y > 247 && m.y < 352)
				{
					tmp = worldsBookIndex + 1;
					//用tmp去试探单词本右边到底还有没有单词，没有的话保持位置不变
					while (word[tmp].isInWordsBook == false && tmp < 3665)
					{
						tmp++;
					}
					if (tmp < 3665)
					{
						worldsBookIndex = tmp;
					}
				}
				//如果点击到了移出单词本
				else if (m.x > 763 && m.x < 871 && m.y > 5 && m.y < 100)
				{
					wordsInWordsBook--;
					word[worldsBookIndex].isInWordsBook = false;
					//将当前的单词移出单词本之后，显示下一个单词
					isNext = false;//表示该单词后面在单词本里面还有没有下一个
					tmp = worldsBookIndex + 1;
					//用tmp去试探单词本右边到底还有没有单词，没有的话保持位置不变
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
						//表明该单词后面在单词本里面没有下一个，那我们寻找单词本中的上一个单词
					{
						tmp = worldsBookIndex - 1;
						//用tmp去试探单词本左边到底还有没有单词，没有的话保持位置不变
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
				//如果点击到了返回
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
		//如果是单词本为空
	{
		loadimage(&EmptyWordsBook, _T("C:\\Users\\ztlzl\\Desktop\\CE-Dict\\emptyWordsBook.jpg"));
		while (1)
		{
			if (MouseHit())
			{
				m = GetMouseMsg();
				//如果鼠标点击
				if (m.mkLButton == true)
				{
					//如果鼠标点击到了返回
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

	settextstyle(80, 0, _T("宋体"));
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
	sortMistakeNumOfWords();//对前面单词的情况进行排序
	while (1)
	{
		if (modeOfReciteWords == 0)
			//背中文
		{
			reciteChinese();
			//如果点击到了返回
			if (isReturnReciteWords == 1)
				break;
		}
		else
			//背英文
		{
			reciteEnglish();
			//如果点击到了返回
			if (isReturnReciteWords == 1)
				break;
		}
	}
}

void reciteChinese()
{
	putimage(0, 0, &ReciteChinese);
	setbkmode(TRANSPARENT);	//设置字体背景色为透明
	MOUSEMSG m;
	while (1)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			//如果鼠标点击背中文
			if (m.mkLButton == true)
			{
				//如果点击到了背中文
				if (m.x > 5 && m.x < 178 && m.y > 5 && m.y < 130)
				{
					modeOfReciteWords = 0;
				}
				//如果点击到了背英文
				else if (m.x > 7 && m.x < 167 && m.y > 145 && m.y < 270)
				{
					modeOfReciteWords = 1;
					break;
				}
				//如果点击到了返回
				else if (m.x > 877 && m.x < 994 && m.y > 1 && m.y < 112)
				{
					isReturnReciteWords = 1;
					userAnswer = -1;
					isNextOrLast = true;
					break;
				}
				//如果点击到了last
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
				//如果点击到了next
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
				//如果点击到了加入单词本
				else if (m.x > 761 && m.x < 875 && m.y > 3 && m.y < 114)
				{
					if (word[reciteWordIndex].isInWordsBook == false)
						word[reciteWordIndex].isInWordsBook = true;
					wordsInWordsBook++;
				}
				//如果点击到了选项A
				else if (m.x > 322 && m.x < 400 && m.y > 185 && m.y < 256)
				{
					userAnswer = 0;
				}
				//如果点击到了选项B
				else if (m.x > 323 && m.x < 390 && m.y > 274 && m.y < 348)
				{
					userAnswer = 1;
				}
				//如果点击到了选项C
				else if (m.x > 326 && m.x < 399 && m.y > 375 && m.y < 436)
				{
					userAnswer = 2;
				}
				//如果点击到了选项D
				else if (m.x > 321 && m.x < 403 && m.y > 466 && m.y < 529)
				{
					userAnswer = 3;
				}
			}
		}

		//如果有键盘消息
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
		answer = rand() % 4;//当前的答案放在哪个选项里面，随机生成
		int num;
		int optionsNum[4];

		//给四个选项随机赋上不是非当前背诵选项的值,并且这四个值不相等
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

		//正确答案在哪个选项上随机生成后开始赋值
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

	settextstyle(30, 0, _T("宋体"));
	settextcolor(BLACK);
	outtextxy(431, 196, A);
	outtextxy(420, 290, B);
	outtextxy(418, 387, C);
	outtextxy(420, 478, D);
	settextstyle(60, 0, _T("宋体"));
	settextcolor(RED);
	outtextxy(374, 85, WORD);

	CHAR tips[30];
	if (userAnswer == -1)
		//用户还未进行作答
	{
		wsprintf(tips, "%s", "请点击屏幕或用键盘作答");
	}
	else if (userAnswer == answer)
	{
		wsprintf(tips, "%s", "作答正确");
	}
	else
	{
		wsprintf(tips, "%s", "作答错误");
	}

	settextstyle(30, 0, _T("宋体"));
	settextcolor(GREEN);
	outtextxy(320, 25, tips);
}

void reciteEnglish()
{
	putimage(0, 0, &ReciteEnglish);
	FlushBatchDraw();
	setbkmode(TRANSPARENT);	//设置字体背景色为透明
	MOUSEMSG m;
	while (1)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			//如果鼠标点击
			if (m.mkLButton == true)
			{
				//如果点击到了加入单词本
				if (m.x > 726 && m.x < 866 && m.y > 2 && m.y < 131)
				{
					if (word[reciteWordIndex].isInWordsBook == false)
						word[reciteWordIndex].isInWordsBook = true;
					wordsInWordsBook++;
				}
				//如果点击到了返回
				else if (m.x > 871 && m.x < 995 && m.y > 1 && m.y < 128)
				{
					isReturnReciteWords = 1;
					numOfLetterInReciteWords = 0;
					userAnswer = -1;
					break;
				}
				//如果点击到了LAST
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
				//如果点击到了NEXT
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
				//如果点击到了背中文
				else if (m.x > 5 && m.x < 201 && m.y > 5 && m.y < 138)
				{
					modeOfReciteWords = 0;
					break;
				}
				//如果点击到了背英文
				else if (m.x > 4 && m.x < 191 && m.y > 153 && m.y < 302)
				{
					modeOfReciteWords = 1;
				}
				//如果点击到了回车
				else if ((m.x > 861 && m.x < 937 && m.y > 289 && m.y < 427) || 
					(m.x > 802 && m.x < 855 && m.y > 348 && m.y < 425))
				{
					isSubmit = true;
					userWord[numOfLetterInReciteWords] = '\0';
					if ((strcmp(word[reciteWordIndex].English, userWord)) == 0)
					{
						userAnswer = 1;//代表作答正确
					}
					else
					{
						userAnswer = 2;//代表作答错误
					}
				}
				//如果点击到了删除
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

		//如果有键盘消息
		if (_kbhit())
		{
			char ch = _getch();
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
				//如果是字母
			{
				if (ch >= 'a' && ch <= 'z')
					//如果是小写
				{
					userWord[numOfLetterInReciteWords] = ch;
				}
				else
					//如果是大写
				{
					userWord[numOfLetterInReciteWords] = ch + 32;
				}
				numOfLetterInReciteWords++;
			}
			else if (ch == 8)
				//删除键（退格）
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
				//回车键
			{
				isSubmit = true;
				userWord[numOfLetterInReciteWords] = '\0';
				if ((strcmp(word[reciteWordIndex].English, userWord)) == 0)
				{
					userAnswer = 1;//代表作答正确
				}
				else
				{
					userAnswer = 2;//代表作答错误
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
		wsprintf(tips, "%s", "请输入单词并按回车");
	}
	else
	{
		if (userAnswer == 1)
		{
			wsprintf(tips, "%s", "作答正确");
		}
		else
		{
			wsprintf(tips, "%s", "作答错误");
		}
	}

	wsprintf(CHINESE, "%s", word[reciteWordIndex].Chinese);

	putimage(0, 0, &ReciteEnglish);
	settextstyle(30, 0, _T("宋体"));
	settextcolor(GREEN);
	outtextxy(320, 25, tips);
	settextstyle(60, 0, _T("宋体"));
	settextcolor(RED);
	outtextxy(375, 182, CHINESE);
	settextcolor(BLACK);
	settextstyle(50, 0, _T("宋体"));
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
			//如果鼠标点击
			if (m.mkLButton == true)
			{
				//如果点击到了中文测验
				if (m.x > 280 && m.x < 583 && m.y > 118 && m.y < 205)
				{
					beginTime = time(NULL);
					testWordsChilese();
				}
				//如果点击到了英文测验
				else if (m.x > 271 && m.x < 576 && m.y > 252 && m.y < 329)
				{
					beginTime = time(NULL);
					testWordsEnglish();
				}
				//如果点击到了返回
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
	//初始化数据
	isSubmitInTestChinese = 0;
	testWordChinese = 0;//当前单词测验显示第几个单词的下标
	isTextedInTestChinese = 0;//当前单词测验已经测验了几个单词
	loadimage(&testWordsChileseIMG, _T("C:\\Users\\ztlzl\\Desktop\\CE-Dict\\testWordsChilese.jpg"));
	int wordsNum[10];//储存着题目的索引
	int optionsNum[4];//储存着四个选项的索引

	//生成不同的10个题目
	do
	{
		for (int i = 0; i < 10; i++)
		{
			wordsNum[i] = rand() % 3665;
		}
	} while (tenNumIsNotEqual(wordsNum) == false);//当生成的题目有重复的时候，就继续生成

	//生成十个不同题目的选项
	for (int i = 0; i < 10; i++)
	{
		chineseExercise[i].index = wordsNum[i];
		//当前的答案放在哪个选项里面，随机生成. 1 2 3 4表示A B C D
		chineseExercise[i].trueAnswer = (rand() % 4) + 1;
		chineseExercise[i].userAnswer = 0;
		
		//用do-while确保四个选项是不相等的
		do
		{
			//给四个选项随机赋上不是非当前背诵选项的值
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

		//正确答案在哪个选项上随机生成后开始赋值
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
			//如果鼠标点击
			if (m.mkLButton == true)
			{
				//如果点击到了选项A
				if (m.x > 325 && m.x < 403 && m.y > 213 && m.y < 265)
				{
					if (chineseExercise[testWordChinese].userAnswer == 0)
						isTextedInTestChinese++;
					chineseExercise[testWordChinese].userAnswer = 1;
				}
				//如果点击到了选项B
				else if (m.x > 321 && m.x < 393 && m.y > 296 && m.y < 348)
				{
					if (chineseExercise[testWordChinese].userAnswer == 0)
						isTextedInTestChinese++;
					chineseExercise[testWordChinese].userAnswer = 2;
				}
				//如果点击到了选项C
				else if (m.x > 324 && m.x < 392 && m.y > 389 && m.y < 449)
				{
					if (chineseExercise[testWordChinese].userAnswer == 0)
						isTextedInTestChinese++;
					chineseExercise[testWordChinese].userAnswer = 3;
				}
				//如果点击到了选项D
				else if (m.x > 323 && m.x < 392 && m.y > 475 && m.y < 535)
				{
					if (chineseExercise[testWordChinese].userAnswer == 0)
						isTextedInTestChinese++;
					chineseExercise[testWordChinese].userAnswer = 4;
				}
				//如果点击到了选项LAST
				else if (m.x > 9 && m.x < 140 && m.y > 539 && m.y < 592)
				{
					testWordChinese--;
					if (testWordChinese < 0)
						testWordChinese = 0;
				}
				//如果点击到了选项NEXT
				else if (m.x > 855 && m.x < 990 && m.y > 546 && m.y < 592)
				{
					testWordChinese++;
					if (testWordChinese >= 9)
						testWordChinese = 9;
				}
				//如果点击到了选项提交
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
				//如果点击到了选项返回
				else if (m.x > 873 && m.x < 993 && m.y > 5 && m.y < 123)
				{
					break;
				}
			}
		}

		//如果有键盘消息
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
				//按键按下回车键，表示提交
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
	setbkmode(TRANSPARENT);	//设置字体背景色为透明
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

	settextstyle(30, 0, _T("宋体"));
	settextcolor(BLACK);
	outtextxy(395, 223, A);
	outtextxy(391, 306, B);
	outtextxy(394, 399, C);
	outtextxy(393, 485, D);
	settextstyle(60, 0, _T("宋体"));
	settextcolor(RED);
	outtextxy(340, 112, wordsInTestChinese);

	CHAR tips[30];
	if (chineseExercise[testWordChinese].userAnswer == 0)
		//用户还未作答
	{
		if (isSubmitInTestChinese == 0)
			//如果还没有点击提交
		{
			wsprintf(tips, "%s", "请用键盘或者用鼠标作答");
		}
		wsprintf(tips, "%s", "这一题您没有提交答案");
	}
	else if (chineseExercise[testWordChinese].userAnswer == 1)
	{
		wsprintf(tips, "%s", "您选择的答案是：A");
	}
	else if (chineseExercise[testWordChinese].userAnswer == 2)
	{
		wsprintf(tips, "%s", "您选择的答案是：B");
	}
	else if (chineseExercise[testWordChinese].userAnswer == 3)
	{
		wsprintf(tips, "%s", "您选择的答案是：C");
	}
	else if (chineseExercise[testWordChinese].userAnswer == 4)
	{
		wsprintf(tips, "%s", "您选择的答案是：D");
	}
	
	settextstyle(20, 0, _T("宋体"));
	settextcolor(GREEN);
	outtextxy(332, 9, tips);

	CHAR remainTest[32];//显示用户还有几个题目没有作答
	if (isSubmitInTestChinese == 0)
		//如果还没有点击提交
	{
		if (isTextedInTestChinese == 0)
		{
			wsprintf(remainTest, "%s", "还有10题没有作答");
		}
		else if (isTextedInTestChinese == 1)
		{
			wsprintf(remainTest, "%s", "还有9题没有作答");
		}
		else if (isTextedInTestChinese == 2)
		{
			wsprintf(remainTest, "%s", "还有8题没有作答");
		}
		else if (isTextedInTestChinese == 3)
		{
			wsprintf(remainTest, "%s", "还有7题没有作答");
		}
		else if (isTextedInTestChinese == 4)
		{
			wsprintf(remainTest, "%s", "还有6题没有作答");
		}
		else if (isTextedInTestChinese == 5)
		{
			wsprintf(remainTest, "%s", "还有5题没有作答");
		}
		else if (isTextedInTestChinese == 6)
		{
			wsprintf(remainTest, "%s", "还有4题没有作答");
		}
		else if (isTextedInTestChinese == 7)
		{
			wsprintf(remainTest, "%s", "还有3题没有作答");
		}
		else if (isTextedInTestChinese == 8)
		{
			wsprintf(remainTest, "%s", "还有2题没有作答");
		}
		else if (isTextedInTestChinese == 9)
		{
			wsprintf(remainTest, "%s", "还有1题没有作答");
		}
		else if (isTextedInTestChinese == 10)
		{
			wsprintf(remainTest, "%s", "作答完毕，确认无误后请点击提交");
		}
	}
	else
		//已经提交了
	{
		settextcolor(RED);
		if (chineseExercise[testWordChinese].userAnswer == chineseExercise[testWordChinese].trueAnswer)
			//如果该题作答正确
		{
			wsprintf(remainTest, "%s", "作答正确");
		}
		else
		{
			wsprintf(remainTest, "%s", "作答错误");
		}
	}
	outtextxy(331, 39, remainTest);

	CHAR trueAnswer[32];//用户点击提交后，如果答案错误则显示正确答案，正确则显示恭喜你
	if (isSubmitInTestChinese == 0)
		//如果还没有点击提交
	{
		wsprintf(trueAnswer, "%s", "");
	}
	else
	{
		if (chineseExercise[testWordChinese].userAnswer == chineseExercise[testWordChinese].trueAnswer)
			//如果该题作答正确
		{
			wsprintf(trueAnswer, "%s", "恭喜你");
		}
		else
		{
			switch (chineseExercise[testWordChinese].trueAnswer)
			{
			case 1:wsprintf(trueAnswer, "%s", "正确答案为A");
				break;
			case 2:wsprintf(trueAnswer, "%s", "正确答案为B");
				break;
			case 3:wsprintf(trueAnswer, "%s", "正确答案为C");
				break;
			case 4:wsprintf(trueAnswer, "%s", "正确答案为D");
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
		outtextxy(10, 110, _T("得分："));
		outtextxy(70, 110, score);
	}

	settextstyle(40, 0, _T("宋体"));
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
	//产生十个不同的单词索引，当做题目
	do
	{
		for (int i = 0; i < 10; i++)
		{
			indexNum[i] = rand() % 3665;
		}
	} while (tenNumIsNotEqual(indexNum) == false);

	//给结构体数组的index赋值并且做必要的初始化
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
			//如果鼠标点击
			if (m.mkLButton == true)
			{
				//如果点击到了submit
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
				//如果点击到了退出
				else if (m.x > 888 && m.x < 996 && m.y > 4 && m.y < 110)
				{
					break;
				}
				//如果点击到了LAST
				else if (m.x > 9 && m.x < 133 && m.y > 543 && m.y < 591)
				{
					testWordEnglish--;
					if (testWordEnglish < 0)
						testWordEnglish = 0;
				}
				//如果点击到了NEXT
				else if (m.x > 846 && m.x < 998 && m.y > 543 && m.y < 599)
				{
					testWordEnglish++;
					if (testWordEnglish >= 9)
						testWordEnglish = 9;
				}	
				//如果点击到了删除键
				else if (m.x > 817 && m.x < 930 && m.y > 368 && m.y < 437)
				{
					englishExercise[testWordEnglish].nextLetterIndex--;
					if (englishExercise[testWordEnglish].nextLetterIndex < 0)
						englishExercise[testWordEnglish].nextLetterIndex = 0;
					//确保字符串已\0结束
					englishExercise[testWordEnglish].userAnswer[englishExercise[testWordEnglish].nextLetterIndex] = '\0';
				}
			}
		}

		//如果有键盘消息
		if (_kbhit())
		{
			char ch = _getch();
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
			{
				if (ch >= 'a' && ch <= 'z')
					//如果是小写
				{
					englishExercise[testWordEnglish].userAnswer[englishExercise[testWordEnglish].nextLetterIndex] = ch;
				}
				else
					//如果是大写
				{
					englishExercise[testWordEnglish].userAnswer[englishExercise[testWordEnglish].nextLetterIndex] = ch + 32;
				}
				englishExercise[testWordEnglish].nextLetterIndex++;
				//确保字符串已\0结束
				englishExercise[testWordEnglish].userAnswer[englishExercise[testWordEnglish].nextLetterIndex] = '\0';
			}
			else if (ch == 8)
				//退格
			{
				englishExercise[testWordEnglish].nextLetterIndex--;
				if (englishExercise[testWordEnglish].nextLetterIndex < 0)
					englishExercise[testWordEnglish].nextLetterIndex = 0;
				//确保字符串已\0结束
				englishExercise[testWordEnglish].userAnswer[englishExercise[testWordEnglish].nextLetterIndex] = '\0';
			}
			else if (ch == 8)
				//回车
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
	setbkmode(TRANSPARENT);	//设置字体背景色为透明
	putimage(0, 0, &testWordsEnglishIMG);

	settextstyle(20, 0, _T("宋体"));
	settextcolor(GREEN);
	CHAR tips[30];
	if (englishExercise[testWordEnglish].nextLetterIndex == 0)
		//用户答案为空
	{
		wsprintf(tips, "%s", "请从键盘键入答案");
	}
	else
	{
		wsprintf(tips, "%s", englishExercise[testWordEnglish].userAnswer);
		outtextxy(332, 9, _T("您的答案是："));
	}
	if (englishExercise[testWordEnglish].nextLetterIndex == 0 &&
		isSubmitInTestEnglish == 1)
	{
		wsprintf(tips, "%s", "此题未作答");
	}
	if (englishExercise[testWordEnglish].nextLetterIndex == 0)
		//用户答案为空
	{
		outtextxy(332, 9, tips);
	}
	else
	{
		outtextxy(445, 9, tips);
	}


	CHAR wordInBox[30];
	wsprintf(wordInBox, "%s", englishExercise[testWordEnglish].userAnswer);
	settextstyle(60, 0, _T("宋体"));
	settextcolor(BLACK);
	outtextxy(261, 352, wordInBox);

	CHAR ChineseExercise[40];
	settextstyle(50, 0, _T("宋体"));
	settextcolor(RED);
	wsprintf(ChineseExercise, "%s", word[englishExercise[testWordEnglish].index].Chinese);
	outtextxy(330, 130, ChineseExercise);

	CHAR remainTest[32];//显示用户还有几个题目没有作答
	settextstyle(20, 0, _T("宋体"));
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
		//如果还没有点击提交
	{
		if (isTextedInTestEnglish == 0)
		{
			wsprintf(remainTest, "%s", "还有10题没有作答");
		}
		else if (isTextedInTestEnglish == 1)
		{
			wsprintf(remainTest, "%s", "还有9题没有作答");
		}
		else if (isTextedInTestEnglish == 2)
		{
			wsprintf(remainTest, "%s", "还有8题没有作答");
		}
		else if (isTextedInTestEnglish == 3)
		{
			wsprintf(remainTest, "%s", "还有7题没有作答");
		}
		else if (isTextedInTestEnglish == 4)
		{
			wsprintf(remainTest, "%s", "还有6题没有作答");
		}
		else if (isTextedInTestEnglish == 5)
		{
			wsprintf(remainTest, "%s", "还有5题没有作答");
		}
		else if (isTextedInTestEnglish == 6)
		{
			wsprintf(remainTest, "%s", "还有4题没有作答");
		}
		else if (isTextedInTestEnglish == 7)
		{
			wsprintf(remainTest, "%s", "还有3题没有作答");
		}
		else if (isTextedInTestEnglish == 8)
		{
			wsprintf(remainTest, "%s", "还有2题没有作答");
		}
		else if (isTextedInTestEnglish == 9)
		{
			wsprintf(remainTest, "%s", "还有1题没有作答");
		}
		else if (isTextedInTestEnglish == 10)
		{
			wsprintf(remainTest, "%s", "作答完毕，确认无误后请点击提交");
		}
	}
	else
		//已经提交了
	{
		settextcolor(RED);
		if (strcmp(englishExercise[testWordEnglish].userAnswer, word[englishExercise[testWordEnglish].index].English) == 0)
			//如果该题作答正确
		{
			wsprintf(remainTest, "%s", "作答正确");
		}
		else
		{
			wsprintf(remainTest, "%s", "作答错误");
		}
	}
	outtextxy(331, 39, remainTest);

	settextstyle(20, 0, _T("宋体"));
	settextcolor(GREEN);
	if (isSubmitInTestEnglish == 1)
		//如果已经点击提交了
	{
		if (strcmp(englishExercise[testWordEnglish].userAnswer, word[englishExercise[testWordEnglish].index].English) == 0)
			//如果该题作答正确
		{
			CHAR trueAnswer[15];
			wsprintf(trueAnswer, "%s", "恭喜你");
			outtextxy(331, 69, trueAnswer);
		}
		else
		{
			CHAR trueAnswer[15];
			wsprintf(trueAnswer, "%s", word[englishExercise[testWordEnglish].index].English);
			outtextxy(331, 69, "正确答案：");
			outtextxy(430, 69, trueAnswer);
		}
	}

	if (isSubmitInTestEnglish == 0)
	{
		nowTime = time(NULL);
	}
	CHAR times[10];
	wsprintf(times, "%ld", (nowTime - beginTime));
	settextstyle(30, 0, _T("宋体"));
	outtextxy(115, 55, times);

	if (isSubmitInTestEnglish == 1)
	{
		CHAR score[2];
		settextcolor(RED);
		wsprintf(score, "%d", trueNumInTestEnglish);
		outtextxy(10, 110, _T("得分："));
		outtextxy(90, 110, score);
	}
}

void loadWordTxt()
{
	readWord();//调用函数从文件中读取单词存入结构体数组
	writeWord();//调用函数把结构体数组的数据以二进制的形式存放到文件中
}

void loadHistoryData()
{
	FILE *fp;
	if ((fp = fopen("C:\\Users\\ztlzl\\Desktop\\cet4Date.txt", "r")) == NULL)
		//读文本
	{
		printf("Can not open the file!");
		exit(0);
	}
	/*
	把如下的三个数据读入
	browseIndex //单词浏览的结构体数组下标
	modeOfReciteWords //背单词的模式，0为背中文，1为背英文，默认为0
	reciteWordIndex //当前背诵的单词的下标，默认为0
	*/
	fscanf(fp, "%d %d %d", &browseIndex, &modeOfReciteWords, &reciteWordIndex);
	fclose(fp);
}

void saveThisData()
{
	FILE *fp;
	if ((fp = fopen("C:\\Users\\ztlzl\\Desktop\\cet4Date.txt", "w")) == NULL) 
		//写文本
	{
		printf("Can not open the file!");
		exit(0);
	}
	char s[5];
	/*
	把如下的三个数据分别放在文件的每一行已达到保存进度的效果 
	browseIndex //单词浏览的结构体数组下标
	modeOfReciteWords //背单词的模式，0为背中文，1为背英文，默认为0
	reciteWordIndex //当前背诵的单词的下标，默认为0
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
rewind(fp);//使得文件读写指针位置重新回到开头，因为在写入文件时文件读写指针在文件末尾
	Word temp;
	while (fread(&temp, sizeof(Word), 1, fp) == 1)
	{
		printf("%s  %s\n", temp.English, temp.Chinese);
	}
*/

/*
int main()
{
	IMAGE imgMenu;//init界面
	setlocale(LC_ALL, "");
	initgraph(1000, 600);
	// 获取窗口句柄
	HWND hwnd = GetHWnd();
	//把游戏名称设置在窗口
	SetWindowText(hwnd, _T("CET4英汉词典"));
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
			//如果鼠标点击
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