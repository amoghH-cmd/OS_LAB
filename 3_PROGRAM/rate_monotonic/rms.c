#include <stdio.h>
#define MAX 10

struct Task {
    int id, e, p, d, r;
};

int gcd(int a, int b){ return b==0 ? a : gcd(b, a%b); }
int lcm(int a, int b){ return (a*b)/gcd(a,b); }

int hyper(struct Task t[], int n){
    int h = t[0].p;
    for(int i=1;i<n;i++) h = lcm(h, t[i].p);
    return h;
}

void RM(struct Task t[], int n, int h){
    printf("\nRM:\n");
    for(int time=0; time<h; time++){
        for(int i=0;i<n;i++)
            if(time % t[i].p == 0) t[i].r = t[i].e;

        int s=-1;
        for(int i=0;i<n;i++)
            if(t[i].r>0 && (s==-1 || t[i].p < t[s].p)) s=i;

        if(s!=-1){ printf("%d:T%d ", time, t[s].id); t[s].r--; }
        else printf("%d:Idle ", time);
    }
}

void EDF(struct Task t[], int n, int h){
    printf("\n\nEDF:\n");
    int dl[MAX];

    for(int i=0;i<n;i++) dl[i]=t[i].d;

    for(int time=0; time<h; time++){
        for(int i=0;i<n;i++)
            if(time % t[i].p == 0){
                t[i].r = t[i].e;
                dl[i] = time + t[i].d;
            }

        int s=-1;
        for(int i=0;i<n;i++)
            if(t[i].r>0 && (s==-1 || dl[i] < dl[s])) s=i;

        if(s!=-1){ printf("%d:T%d ", time, t[s].id); t[s].r--; }
        else printf("%d:Idle ", time);
    }
}

void PRO(struct Task t[], int n, int h){
    printf("\n\nPROPORTIONAL:\n");
    int turn=0;

    for(int time=0; time<h; time++){
        for(int i=0;i<n;i++)
            if(time % t[i].p == 0) t[i].r = t[i].e;

        int c=0;
        while(c<n && t[turn].r==0){
            turn=(turn+1)%n; c++;
        }

        if(c<n){
            printf("%d:T%d ", time, t[turn].id);
            t[turn].r--; turn=(turn+1)%n;
        } else printf("%d:Idle ", time);
    }
}

int main(){
    int n;
    printf("Enter tasks: ");
    scanf("%d",&n);

    struct Task t[MAX];

    for(int i=0;i<n;i++){
        t[i].id=i+1;
        printf("E P D: ");
        scanf("%d%d%d",&t[i].e,&t[i].p,&t[i].d);
    }

    int h = hyper(t,n);
    printf("\nHyperperiod=%d\n",h);

    RM(t,n,h);
    EDF(t,n,h);
    PRO(t,n,h);

    return 0;
}
