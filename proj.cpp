#include<stdio.h>

struct data
{
    int number;
    int arrival_time;
    int burst_time;
    int rt;
    int ft;
    int st;
    int waiting_time;
    int tat;
};

int fr = -1, rr = -1;
struct data priorQueue[51];
void LJF(struct data x) {
    int i, j;
    for (i=0;i<=rr;i++)
    {
        if (x.burst_time>priorQueue[i].burst_time)
        {
            for (j=rr+1;j>i;j--)
            {
                priorQueue[j]=priorQueue[j - 1];
            }
            priorQueue[i] = x;
            return;
        }
    }
    priorQueue[i] = x;
}

void SJF(struct data x) {
    int i, j;
    for (i=0;i<=rr;i++)
    {
        if (x.burst_time<priorQueue[i].burst_time)
        {
            for (j =rr+1;j>i;j--)
            {
                priorQueue[j] = priorQueue[j - 1];
            }
            priorQueue[i] = x;
            return;
        }
    }
    priorQueue[i] = x;
}

void Push(struct data x, int y) {
    if(fr==-1&&rr==-1)
    {
        fr++;
        rr++;
        priorQueue[rr] = x;
        return;
    }
    else
    {
    	if(y==1)
        LJF(x);
        else
        SJF(x);
    }
    rr++;
}

void Pop()
{
    int i;
    if(fr==-1&&rr==-1)
    {
        return;
    }
    for (i=0;i<rr;i++)
    {
        priorQueue[i] = priorQueue[i + 1];
    }
    rr--;
    if (rr==-1)
        fr=-1;
}

int Empty()
{
    return ((fr==-1 && rr==-1));
}
struct data pqTop()
{
    return priorQueue[fr];
}

void calculation(struct data p[],int g[],int n,int tt) {

    int i, j;
    float avgWt = 0, avgTrt = 0;
    for (i=0;i<n;i++)
    {
        for (j=tt;j>=0;j--)
        {
            if (g[j]==i+1)
            {
                p[i].ft=j+1;
                break;
            }
        }
    }

    for(i=0;i<n;i++)
    {
        for (j=0;j<tt;j++)
        {
            if (g[j]==i+1)
            {
                p[i].st=j;
                break;
            }
        }
    }
    for (i=0;i<n;i++)
    {
        p[i].waiting_time=p[i].ft-p[i].arrival_time-p[i].burst_time;
        p[i].tat=p[i].waiting_time+p[i].burst_time;
        avgWt+=p[i].waiting_time;
        avgTrt+=p[i].tat;
    }
    avgWt /= n;
    avgTrt /= n;
    printf("\n");
    printf("Average Waiting Time And Average Turn Around Time \n\n");
    printf("%f %f", avgWt, avgTrt);
    printf("\n");

}

void function(struct data p[],int n,int x)
{
    int tt=0,i,j;
    tt += p[0].arrival_time+p[0].burst_time;
    for (i=1;i<n;i++)
    {
        if (tt<p[i].arrival_time)
            tt=p[i].arrival_time;
        tt+=p[i].burst_time;
    }
    int ghart[tt],cpu_state=0;
    for (i=0;i<tt;i++)
        ghart[i] = -1;
    struct data current;
    for (i=0;i<tt;i++)
    {
        for (j=0;j<n;j++)
        {
            if (i==p[j].arrival_time)
            {
                	Push(p[j], x);
            }
        }
        if (cpu_state==0)
        {
            if (!Empty())
            {
                current = pqTop();
                Pop();
                cpu_state = 1;
            }
        }
        if (cpu_state==1)
        {
            current.burst_time--;
            ghart[i] = current.number;
            if (current.burst_time==0)
            {
                cpu_state=0;
            }
        }
    }

    for ( i=0;i<tt;i++)
        printf("%d ",ghart[i]);
    calculation(p,ghart,n,tt);
}

int main()
{

    int n,i;
    printf("enter number of process");
    scanf("%d", &n);
    struct data p[n];
    for (i=0;i<n;i++)
    {
    	scanf("%d", &p[i].number);
    	printf("enter arrival time for process %d :",i+1);
        scanf("%d",&p[i].arrival_time);
        p[i].burst_time = p[i].arrival_time * 2;
    }

    function(p, n, 1);
    printf("\n");
    function(p, n, 2);
}
