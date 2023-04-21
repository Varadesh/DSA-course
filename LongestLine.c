#include<stdio.h>
#include<string.h>
int longest(char s[100][100],int a)
{
    int count1[25],k;
    for(int i=0;i<a;i++)
    {  
        int count=0;
        for(int j=0;s[i][j]!='\0';j++)
        {
            count++;
        }
        count1[i]=count;
        printf("Length of %dth string is %d\n",i+1,count1[i]);
    }
    int max=count1[0];
    for(int i=0;i<a;i++)
    {
        if(max<count1[i])
        {
            max=count1[i];
            k=i;
        }
    }
    printf("Longest length is %d\n",max);
    return k;

}
int main()
{
    char s[5][100];
    int a;
    printf("Enter the numbers of lines to be read\n");
    scanf("%d",&a);
    for(int i=0;i<a+1;i++)
    {  
        gets(s[i]);
    }
    for(int i=0;i<a+1;i++)
    {
        puts(s[i]);
    }
    int b=longest(s,a);
    puts(s[b]);
}