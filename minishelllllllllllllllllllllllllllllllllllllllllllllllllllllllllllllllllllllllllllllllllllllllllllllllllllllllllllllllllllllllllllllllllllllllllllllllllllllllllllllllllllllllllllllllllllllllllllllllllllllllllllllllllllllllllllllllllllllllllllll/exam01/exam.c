



// initi the args la ne5od alrgs men luser input  than check la nle2e %  pass the ft_format check  wich  fomt  we have   to kno[w whta to d o]


void ft_puthex(unsigned int n ,  char  c ,int *len)
{
    if (n >= 16)
    {
        ft_puthex(n/16,c,len);
        ft_puthex(n%16,c,len);
    };
    if (n < 16)
    {
        if (x == ' x' )
    }
}


void  ft_format(char c,int *;en,va_list args)
{
    if (c == 's') 
        ft_putstr(va_arg(args,char *),len);
    if ( c == 'd')
        ft_putnbr(va_arg(args,int),len);
    if ( c == 'x')
        ft_puthex(va_arg(args,unsigned int),c,len);
}

int ft_printf(const char  *str,...)
{
    int i =0 ;
    int len  =0 ;
    va_list args;

    va_start (args,str);
    while(str[i])
    {
        if (str[i] == '%')
        {
            i++;
            ft_format(str[i], &len,args);
        }
        else{
            write(1,&str[i].1);
            len++;
        };
        i++;
    }
    va_end(args);
    return (len);
}