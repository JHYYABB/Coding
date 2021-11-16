/*
 * @Author: 知会_X
 * @Date: 2021-11-15 23:39:27
 * @LastEditTime: 2021-11-16 23:00:59
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \undefinedc:\Users\Ming\Desktop\Coding Pratice\C\Untitled-1.c
 */

/*
 * @Author: 知会_X
 * @Date: 2021-11-15 23:39:27
 * @LastEditTime: 2021-11-15 23:39:28
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \undefinedc:\Users\Ming\Desktop\Coding Pratice\C\Untitled-1.c
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>

//存储在字典中不同单词的首字母在二维字符列表中的位置和相同首字母的单词
typedef struct{
    char first_letter;
    int x[20],y[20];
    int xy_num;
    char *dict[20];
    int dict_size;
}WORDS;

/*
    功能：获得字典中所有单词的首字母，并将所有首字母以字符串的形式储存在first_letters中
    参数：
        1.储存首字母的字符串的一维数组
        2.储存单词的字典(二维数组)
        3.已知字典的阶数
*/
void Get_First_Letters(char *first_letters,char *dict[20],int dict_size)
{
    int i,j;
    first_letters[0] = '\0';//将fir_letter转化为字符串

    for(i=0,j=0;i<dict_size;i++)
    {
        /*
            若字典中的单词的首字母在first_letter中为空，
            则在first_letter中添加字母
        */
       //printf("%c\n",*dict[i]);
        if(strchr(first_letters,*dict[i])==NULL)
        {        
            first_letters[j++] = *dict[i];
            first_letters[j] = '\0';
        }
    }
    //#define __Get_First_Letters
    #ifdef  __Get_First_Letters
        printf("first_letter %s\n",first_letters);
    #endif
}

/*
    功能：将每个首字母在字典中对应的单词储存到每个首字母对应的字典里
    参数：
         1.WORDS类型的结构体数组
         2.已知字典的地址
         3.储存首字母组合成的字符串的数组首地址
         4.已知字典的阶数
*/
void word_init(WORDS *word,char *dict[4],char *first_letter,int dict_size)
{
    int i,j,k=0;
    int fl_size = strlen(first_letter);

    
    for(i=0;i<fl_size;i++)
    {
        word[i].first_letter = first_letter[i];
        for(j=0;j<dict_size;j++)
        {
            if(word[i].first_letter==*dict[j])
                word[i].dict[k++] = dict[j];
        }
        word[i].dict_size = k;
        k=0;
    }

    //#define __word_init
    #ifdef __word_init
    for(i=0;i<fl_size;i++)
    {
        for(j=0;j<dict_size;j++)
        {   
            printf("%s\n",word[i].dict[j]);
        }
    }
    #endif
}

/*
    功能：寻找每个首字母在二维字符列表中的所有位置
    参数：
        1.WORDS类型的结构体数组
        2.二维字符列表的地址（指向二维数组的指针）
        3.由首字母组合成的字符串长度
        4.二维字符列表的阶数
*/
void get_xy(WORDS *word,char (*puzzle)[4],int fl_size,int puzzle_size)
{
    int i,j,k,m=0,test_i;
    for(i=0;i<fl_size;i++)
    {
        m = 0;
        for(j=0;j<puzzle_size;j++)
        {
            for(k=0;k<puzzle_size;k++)
            {
                if(word[i].first_letter==puzzle[j][k])
                {    
                    word[i].x[m] = j;
                    word[i].y[m++] = k;
                }
            }
        }
        word[i].xy_num = m;

        //#define __get_xy
        #ifdef __get_xy
        for(test_i=0;test_i<word[i].xy_num ;test_i++)
            printf("xy_num = %d %c -> %d %d\n",word[i].xy_num,word[i].first_letter,word[i].x[test_i],word[i].y[test_i]);
        #endif
    }

}

/*
    实现思想:  将输入的字符与输入的单词对应位置进行比对，只要比对成功就直接进入下一次
              比对，直至指向字典单词的指针已经指向空字符，则比对成功；其中若有一次比
              对失败，直接进入下一个单词的比对
    功能：逐个比对字符
    参数：
        1.二维字符列表的地址（指向二维数组的指针）
        2.WORDS类型的结构体数组
        3.首字母所对应的单词
        4.模式：
            1 -> 横向比对       n=1,方向向右;n=-1,方向向左
            2 -> 纵向比对       n=1,方向向下;n=-1,方向向上
            3 -> 斜向右比对     n=1,方向向下;n=-1,方向向上
            4 -> 斜向左比对     n=1,方向向下;n=-1,方向向上
        5.决定检查方向，参考[4.]
    
*/
void comp_chr(char (*puzzle)[4],WORDS *word,char *dict_word,char mode,int n,int j)
{
    switch (mode)
    {
        case 1:
            if(word->y[j]+n<5&&n>0)
            {
                if(dict_word[n]=='\0') 
                {
                    printf("x=%d y=%d %s\n",word->x[j],word->y[j],dict_word);
                    return ;
                }
                if(puzzle[word->x[j]][word->y[j]+n] == dict_word[n])
                {
                    comp_chr(puzzle,word,dict_word,mode,n+1,j);
                }
            }
            else if(word->y[j]+n>=-1&&n<0)
            {
                if(dict_word[-n]=='\0') 
                {
                    
                    printf("x=%d y=%d %s\n",word->x[j],word->y[j],dict_word);
                    return;
                }
                if(puzzle[word->x[j]][word->y[j]+n] == dict_word[-n])
                {
                    comp_chr(puzzle,word,dict_word,mode,n-1,j);
                }                
            }
            break;
        case 2:
            if(word->x[j]+n<5&&n>0)
            {
                if(dict_word[n]=='\0') 
                {
                    printf("x=%d y=%d %s\n",word->x[j],word->y[j],dict_word);
                    return ;
                }
                if(puzzle[word->x[j]+n][word->y[j]] == dict_word[n])
                {
                    comp_chr(puzzle,word,dict_word,mode,n+1,j);
                }
            }
            else if(word->x[j]+n>=-1&&n<0)
            {
                if(dict_word[-n]=='\0') 
                {
                    
                    printf("x=%d y=%d %s\n",word->x[j],word->y[j],dict_word);
                    return;
                }
                if(puzzle[word->x[j]+n][word->y[j]] == dict_word[-n])
                {
                    comp_chr(puzzle,word,dict_word,mode,n-1,j);
                }                
            }
            break;
        case 3:
            if(word->x[j]+n<5&&word->y[j]+n<5&&n>0)
            {
                if(dict_word[n]=='\0') 
                {
                    printf("x=%d y=%d %s\n",word->x[j],word->y[j],dict_word);
                    return ;
                }
                if(puzzle[word->x[j]+n][word->y[j]+n] == dict_word[n])
                {
                    comp_chr(puzzle,word,dict_word,mode,n+1,j);
                }
            }
            else if(word->x[j]+n>=-1&&word->y[j]+n>=-1&&n<0)
            {
                if(dict_word[-n]=='\0') 
                {
                    
                    printf("x=%d y=%d %s\n",word->x[j],word->y[j],dict_word);
                    return;
                }
                if(puzzle[word->x[j]+n][word->y[j]+n] == dict_word[-n])
                {
                    comp_chr(puzzle,word,dict_word,mode,n-1,j);
                }                
            }
            break;
        case 4:
            if(word->x[j]+n<5&&word->y[j]-n>=-1&&n>0)
            {
                if(dict_word[n]=='\0') 
                {
                    printf("x=%d y=%d %s\n",word->x[j],word->y[j],dict_word);
                    return ;
                }
                if(puzzle[word->x[j]+n][word->y[j]-n] == dict_word[n])
                {
                    comp_chr(puzzle,word,dict_word,mode,n+1,j);
                }
            }
            else if(word->x[j]+n>=-1&&word->y[j]-n<5&&n<0)
            {
                if(dict_word[-n]=='\0') 
                {
                    printf("x=%d y=%d %s\n",word->x[j],word->y[j],dict_word);
                    return;
                }
                if(puzzle[word->x[j]+n][word->y[j]-n] == dict_word[-n])
                {
                    comp_chr(puzzle,word,dict_word,mode,n-1,j);
                }                
            }
            break;
        default:
            printf("MODE ERROR\n");
            break;
    }
}

/*
    实现思想: 从首字母在二维字符列表中的第一个坐标开始，从各个方向延申，
             使得每个单词与字母对应字典的单词中的对应字符进行逐个比对
    功能：比对字符串
    参数：
        1.WORDS类型的结构体数组
        2.二维字符列表
        3.由首字母组合成的字符串长度
*/
void comp_str(WORDS *word,char (*puzzle)[4],int fl_size)
{
    int i,j,k;
    for(i=0;i<fl_size;i++)
    {
        for(j=0;j<word[i].xy_num;j++)
        {
            for(k=0;k<word[i].dict_size;k++)
            {
                comp_chr(puzzle,&word[i],word[i].dict[k],1,1,j);
                comp_chr(puzzle,&word[i],word[i].dict[k],1,-1,j);
                comp_chr(puzzle,&word[i],word[i].dict[k],2,1,j);
                comp_chr(puzzle,&word[i],word[i].dict[k],2,-1,j);
                comp_chr(puzzle,&word[i],word[i].dict[k],3,1,j);
                comp_chr(puzzle,&word[i],word[i].dict[k],3,-1,j);
                comp_chr(puzzle,&word[i],word[i].dict[k],4,1,j);
                comp_chr(puzzle,&word[i],word[i].dict[k],4,-1,j);
            }
        }
    }
}

int main(void)
{   //已知条件
    char puzzle[4][4] = {
        {'w','a','r','l'},
        {'t','w','l','c'},
        {'r','a','a','c'},
        {'c','a','c','c'}
    };
    char *dict[] = {"woah","cat","call","war"};


    char first_letter[26];//储存字典中首字母，将所有首字母转化为字符串
    WORDS word[26]={0};//最多不同26个首字母

    Get_First_Letters(first_letter,dict,sizeof(dict)/sizeof(char *));
    word_init(word,dict,first_letter,4);
    get_xy(word,puzzle,strlen(first_letter),sqrt(sizeof(puzzle)/sizeof(char)));
    comp_str(word,puzzle,sizeof(first_letter));
    
    printf("\nGAME OVER\n");
    return 0;
}