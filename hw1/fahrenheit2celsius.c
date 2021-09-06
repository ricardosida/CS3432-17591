#include <stdio.h>


float convert (float f);

int main() {
	  int fahr;
      float celsius;
	  int lower, upper, step;
	
	  lower = 0;	/* lower limit of temperature table */
	  upper = 300;	/* upper limit */
	  step = 20;	/* step size */

	  fahr = lower;
	  while (fahr <= upper) {
          celsius = convert(fahr);
          printf("%d\t%.4f\n",fahr, celsius);
		  fahr = fahr + step;
	  }
}
float convert (float f){
          return 5 * (f-32) / 9;
          
}