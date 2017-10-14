#include <stdio.h>
#include <stdlib.h>
#define RED "\033[31m"
#define RESET "\033[0m"

unsigned int power(unsigned int a,unsigned int b) {
    unsigned int p = 1;
    for(unsigned int i = 0;i < b;i++)
        p *= a;
    return p;
}

unsigned int total_parity_bits2 (unsigned int N) {
  return (N == 3) ? 2 : (N <= 7) ? 3 : (N<=15) ? 4: (N<=31) ? 5: (N<=63) ? 6: (N<=127) ? 7:8;
}

unsigned int total_parity_bits (unsigned int N) {
    return (N == 1) ? 2 :(N<=4) ?3 : (N<=11) ?4 : (N<=26) ?5 : (N<=57) ?6 : (N<=120) ?7 : 8;
}

void print_final(int *y,unsigned int N) {
    unsigned int g = 1;
    for(unsigned int i = 1;i < N;i++) {
        if(i != g) {
            printf("  ");
        }
        else {
            printf("P ");
            g*=2;
        }
    }
    printf("\n");
    for(int i = 0;i < N;i++)
        printf("%d ",y[i]);
}

int main() {
  int sel = 0;
  while(sel != 3) {
  printf("Choose an operation:\n 1)Produce Hamming code in a message\n 2)Check/find error\n 3)Exit\n");
  scanf("%d",&sel);
  if(sel == 1) {
    unsigned int n;
    printf("Enter size of the message: ");      /* Message should be smaller or equal to 247 ( sizeof(message) <= 247 ) */
    scanf("%u",&n);
    char *x = calloc(n+1,sizeof(char));
    printf("Enter message: ");
    scanf("%s",x);
    unsigned int a = total_parity_bits(n);
    printf("\n\n\n");
    printf("Number of parity bits = %u\n",a);
    int *y = calloc((a+n),sizeof(int));
    for(unsigned int i = 2;i < a + 1;i++) {                                 // This section inputs the values that the user inserted into the corresponding positions in the final message
        if(i == a) {
            for(unsigned int k = (power(2,i-1)-i);k < (n+a+1);k++)
                y[k+i] = (int)x[k]-48;
        }
        else {
            for(unsigned int k = (power(2,i-1)-i);k < power(2,i)-i-1;k++)
                y[k+i] = (int)x[k]-48;
        }
    }                                                                       // and ends here
    free(x);
    for(unsigned int i = 1;i < power(2,a);i*=2) {                           // This section calculates the value of parity bits (without % 2)
        for(unsigned int j = (i-1);j < n+a;j += 2*i) {
            for(unsigned int k = 0;k < i;k++) {
                if(k+j < n+a)
                    y[i-1] += y[k+j];
            }
        }
    }                                                                       // and ends here
    for(unsigned int i = 1;i < power(2,a);i*=2)                             // This section turns the values from the previous step to binary (with % 2)
        y[i-1] %= 2;                                                        // and ends here
    print_final(y,n+a);
    printf("\n\n\n\n\n\n");
  }
  else if(sel == 2) {
    int o = 0,s = 0;
    unsigned int P,N;
    printf("Enter message size: ");
    scanf("%u",&N);
    P = total_parity_bits2(N);
    char *x = calloc(N+1,sizeof(char));
    printf("Enter message to be checked: ");
    scanf("%s",x);
    int *y = calloc(N,sizeof(int));
    for(int i = 0;i < N;i++)
      y[i] = (int)x[i]-48;
    free(x);
    int *p = calloc(P,sizeof(int));
    for(unsigned int i = 1;i < power(2,P);i*=2) {                           // This section calculates the value of parity bits (without % 2)
        for(unsigned int j = (i-1);j < N;j += 2*i) {
            for(unsigned int k = 0;k < i;k++) {
                if(k+j < N)
                    p[o] += y[k+j];
            }
        }
        o = o + 1;
    }
    o = 0;
    for(int i = 1;i < power(2,P);i*=2) {
      if(p[o] % 2 != 0) {
        s+=i;
      }
      o = o + 1;
    }
    if(s == 0)
      printf("\n\nNo errors\n");
    else {
      printf("\n\nThere is an error:\n");
      y[s-1] = (y[s-1] == 1) ? 0 : 1;
      printf("Corrected Message: ");
      for(int i = 0;i < N;i++) {
  		  if(i != s-1)
          printf("%d",y[i]);
        else
          printf( RED "%d" RESET,y[i]);
  	    }
      }
    printf("\n\n\n\n\n\n");
  }
  }
  return 0;
}
