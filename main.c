#include<stdio.h>
#include<stdbool.h>


void delete_comments(FILE *, FILE*);
void skip_star( FILE * );
void skip_slash(FILE * ,FILE *);
void rewrite(FILE *, FILE * ,char *);



int main( int argc, char * argv[] ){
    FILE *source , *txt ;
    char file_name[100]="";
    scanf("%s", &file_name);
    //open file with cpp or c extension.
    //If file is not in project folder, full path need to be written.
    source = fopen(file_name , "r") ;
    // Open temporary txt file where we will copy our code without comments
    txt = fopen("temp.txt" , "w") ;
    if (source==NULL )  //If file doesnt exists
    {
        printf ("Wrong path or file does not exists ! \n") ;
        return  0;
    }
    delete_comments(source,txt);
    rewrite(source,txt,file_name);
    remove("temp.txt");


    return 0 ;
}
/* main func where 2 file must be passed. If file cannot be opened it returns false */
void delete_comments(FILE *source, FILE* txt){
    int ch , prev=0 ;
    bool InQuote=false;


    while ((ch=getc(source))!=EOF )//looping through source file
    {
        if ( !InQuote )
        {
            if ( ch=='/' )      //If we find '/' then we need to check next character
            {
                prev=ch ;
                ch= getc(source) ;
                if(ch=='*')     //If next character is * we enter skip_star function
                    skip_star(source);
                else if(ch=='/')  //If next character is / we enter skip_slash function
                    skip_slash(source,txt);
                else
                {
                    putc(prev , txt) ;
                    putc(ch , txt) ;
                }
            }
            else putc( ch ,txt ) ;
        }
        else  putc(ch , txt) ;

        if ( ch=='\"')
            InQuote = !InQuote ;
        prev = ch ;
    }
    fclose(source) ;
    fclose(txt) ;

}

void skip_star( FILE *source )
{
    int prev=0 , ch ;

    while ((ch=getc(source))!=EOF)
    {
        if ( prev== '*' && ch == '/')
            return ;
        else
            prev=ch ;
    }
}

void skip_slash(FILE * source, FILE * txt)
{
    int ch ;
    while ( (ch=getc(source))!='\n' && ch!=EOF )
    {}
    if(ch=='\n')
     putc(ch,txt);
}
// rewrite back to our source file
void rewrite(FILE *cpp, FILE *txt , char* c)
{
    cpp=fopen(c, "w");
    txt=fopen("temp.txt", "r");
    int ch;
    if(txt == NULL)
    {
        printf("EMPTY\n");
    }
    else{
        while((ch=getc(txt))!=EOF)
        {
            putc(ch, cpp);
        }
    }
}
