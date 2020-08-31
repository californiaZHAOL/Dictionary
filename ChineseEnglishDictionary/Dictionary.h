#pragma once
#include<conio.h>
#include <graphics.h> 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>
#include<wchar.h>
#include <ctype.h>
#pragma comment(lib,"Winmm.lib")

//储存单词的结构体，用typedef定义别名为Word
typedef struct
{
	char English[15];
	char Chinese[40];
	int index;//该结构体的索引
	bool isInWordsBook;//该单词是否在单词本中
}Word;
//储存单词的结构体数组
Word word[3665];

//储存单词中文测验中每个题目的结构体，用typedef定义别名为ChineseExercise
typedef struct
{
	//每个选项中内容的索引
	int a;
	int b;
	int c;
	int d;
	int trueAnswer;//正确答案，用1 2 3 4表示A B C D
	int userAnswer = 0;//用户给出的答案，0表示未给出，正确答案，用1 2 3 4表示A B C D
	int index;//该题单词的索引
}ChineseExercise;
//储存测验单词中文时的十个题目
ChineseExercise chineseExercise[10];

//储存单词英文测验中每个题目的结构体，用typedef定义别名为EnglishExercise
typedef struct
{
	int index;//该题单词的索引
	int nextLetterIndex = 0;//下一个字母放在结构体里面的字符数组里面的索引
	char userAnswer[15];//用户的答案
}EnglishExercise;
//储存测验单词英文时的十个题目
EnglishExercise englishExercise[10];

//这个结构体里面包含了每个单词的索引，以及每个单词错误的次数
typedef struct
{
	int index;//该单词的索引
	int errorTimes = 0;//错误次数，0表示没有错过，错一次就加1，如果答对一次就减1,0为下限
}mistakeNumOfWords;
mistakeNumOfWords notSortWords[3665];//未排序过后的
mistakeNumOfWords sortedWords[3665];//排序过后的

int browseIndex = 0;//单词浏览的结构体数组下标
int isReturnBrowseWords = 0;//标识按退出键退出单词浏览
int isReturnWordsBook = 0;//标识按退出键退出单词本
int isReturnReciteWords = 0;//标识按退出键退出单词背诵
int browseSearchNum = 0;//单词浏览界面下查询框显示的数字
int worldsBookIndex = 0;//单词本的初始下标
int wordsInWordsBook = 0;//在单词本里面的单词个数
int modeOfReciteWords = 0;//背单词的模式，0为背中文，1为背英文，默认为0
int insertReciteWordIndex = 0;//插入的背诵的单词错误次数结构体的下标，为了实现强化记忆功能
bool isNextOrLast = true;//表示在背单词的模式下，是否对背单词的题目进行更换，默认为更换
bool isSubmit = false;//背单词背中文模式下已经提交过答案
bool isInsert = true;//表示当前的单词是否是插入进去的
int userAnswer = -1;//背单词模式下用户点击的回答,-1表示用户还没有进行选择
int answer;//背单词背中文模式下正确答案的序号
int numOfLetterInReciteWords = 0;//在背单词背英语的界面用户输入的单词的长度，默认为0
int modeOfTestWords = 0;//测验单词时的模式，0为测验英文，1为测验英文，2为中英文混合测验，默认为0
int isReturnTestWords = 0;//单词测验下如果退出则为1,默认为0
int testWordChinese = 0;//当前单词中文测验显示第几个单词的下标
int testWordEnglish = 0;//当前单词英文测验显示第几个单词的下标
int isTextedInTestChinese = 0;//当前单词测验中文已经测验了几个单词
int isTextedInTestEnglish = 0;//当前单词测验英文已经测验了几个单词
int trueNumInTestChinese = 0;//测验单词测验中文对了几个
int trueNumInTestEnglish = 0;//测验单词测验英文对了几个
int isSubmitInTestChinese = 0;//测验单词测验中文是否点击了提交，0为未点击，1为已点击
int isSubmitInTestEnglish = 0;//测验单词测验英文是否点击了提交，0为未点击，1为已点击
int reciteWordIndex = 0;//当前顺序背诵的单词的下标，默认为0
int reciteStrengthenWordIndex = 0;//当前强化背诵的单词在排序数组当中的下标，默认为0
int maxIndex;//判断强化记忆单词的在排序数组当中的最大值,最大值为maxIndex，且不包含maxIndex
int isReturnSearchWords;//在查询的界面下，标记是否退出，为1则表示退出，0表示不退出
int lengthOfSearchEnglishToChinese = 0;//英文搜索中文模式,用户输入的下一个字母储存在数组里面的下标
int wordIndexInSearchEnglishToChinese = -1;//英文搜索中文模式,如果搜索到了，则储存的是下标，未搜索到为-1
bool isSubmitSearchEnglishToChinese = false;//英文搜索中文模式,用户是否提交过
CHAR A[40];//背单词背中文模式下选项A的内容
CHAR B[40];//背单词背中文模式下选项B的内容
CHAR C[40];//背单词背中文模式下选项C的内容
CHAR D[40];//背单词背中文模式下选项D的内容
CHAR searchEnglishToChinese[25] = {0};//英文搜索中文模式，用户的答案
CHAR userWord[20];//在背单词背英语的界面用户输入的单词
time_t nowTime, beginTime;//测验计时开始和结束

IMAGE imgMenu;//init界面
IMAGE browseWords;//browseWords界面
IMAGE WordsBook;//单词本界面
IMAGE EmptyWordsBook;//空的单词本界面
IMAGE ReciteChinese;//顺序背中文的界面
IMAGE ReciteEnglish;//顺序背英文的界面
IMAGE EndReciteStrengthenWord;//强化记忆没有强化记忆数据时的界面
IMAGE ReciteStrengthenChinese;//强化背中文的界面
IMAGE ReciteStrengthenEnglish;//强化背英文的界面
IMAGE reciteInit;//背单词初始选择界面
IMAGE testWords;//单词测验初始界面
IMAGE testWordsChileseIMG;//单词测验测验中文界面
IMAGE testWordsEnglishIMG;//单词测验测验英文界面
IMAGE SearchInit;//搜索功能的初始界面
IMAGE EnglishToChinese;//英文搜索中文的界面
IMAGE ChineseToEnglish;//中文搜索英文的界面

void readWord();//从单词文件中读取单词存放在结构体数组中
void writeWord();//将结构体数组以二进制的形式写入文件
void loadWordTxt();//载入单词文本文件
void loadHistoryData();//载入历史数据
void saveThisData();//储存这次运行的数据
void BrowseWords();//浏览单词
void init();//初始化数据和界面
void drawBrowseWords();//画浏览单词界面的界面
void wordsBook();//单词本选项界面
void drawWordsBook();//画单词本界面
void drawEmptyWordsBook();//画空的单词本
void reciteEnglish();//背英文
void reciteChinese();//背中文
void choseReciteWords();//背单词选择模式的函数
void reciteStrengthenWords();//强化背单词的函数
void reciteWords();//顺序背单词的函数
void drawReciteChinese();//画顺序背单词中背中文的界面
void drawReciteEnglish();//画顺序背单词中背英文的界面
void drawReciteStrengthenChinese();//画强化背单词中背中文的界面
void drawReciteStrengthenEnglish();//画强化背单词中背英文的界面
void reciteStrengthenChinese();//强化背单词背中文界面
void reciteStrengthenEnglish();//强化背单词背英文界面
void testWordsInit();//单词测验界面的初始化
void testWordsEnglish();//单词测验中测验英语
void testWordsChilese();//单词测验中测验中文
void drawTestWordsChilese();//画单词测验中测验中文
void drawTestWordsEnglish();//画单词测验中测验英文
bool tenNumIsNotEqual(int *a);//判断一个有十个数的数组里面的数互不相等
bool fourNumIsNotEqual(int *a);//判断一个有四个数的数组里面的数互不相等
void sortMistakeNumOfWords();//给保存错误次数的结构体数组排序
void searchInit();//搜索功能的初始界面
void englishToChinese();//英文搜索中文的界面
void chineseToEnglish();//中文搜索英文的界面
void drawEnglishToChinese();//画英文搜索中文的界面
void drawChineseToEnglish();//画中文搜索英文的界面
int comp(const void*a, const void*b);//qsort的比较函数
void fromEnglishSearchChinese(char *a);//由给定的英文搜索中文，返回下标，没有搜索到返回-1
void endReciteStrengthenWord();//结束强化记忆的页面
void click();//发出一次鼠标点击音效