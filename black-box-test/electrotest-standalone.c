#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*

*/
int e_resistance(float orig_resistance, float *res_array);
float calc_power_r(float u, float r);
float calc_power_i(float u, float i);
float calc_resistance(int count, char conn, float *array);

int main()
{
	float volt=0;
	float resistance;
	float power;
	char conn;
	int component_count=0;
	int replacements=0;

//	spänning att använda
	if(volt <= 0)
	{
		printf("Ange spänningskälla i V (>0): \n");
		scanf("%f", &volt);
	}	

	printf("Ange koppling[S|P]: \n");
	scanf(" %c", &conn);
		
//	antal komponenter att använda
	if(component_count <= 0)
	{
		printf("Ange antal komponenter: \n");
		scanf("%d", &component_count);
	}

//	minnesallokering för angivet antal komponenter	
	float *res_array = malloc(component_count * sizeof(float));

//	skriva angivna resistanser till array
	for(int i=0; i<component_count; i++)
	{
		printf("Komponent %d i ohm: ", i+1);
		scanf("%f", &res_array[i]);
	}

//	beräknad resistans för angivna resistanser
	resistance = calc_resistance(component_count, conn, res_array);
	printf("Ersättningsresistans: %.1f\n", resistance);

//	effekt med angiven resistans
	power = calc_power_r(volt, resistance);
	printf("Effekt: %.1f\n", power);
	
	
	printf("Ersättningsresistancer i E12-serien kopplade i serie: \n");

//	ersättningsresistanser - for-loop? 
	replacements = e_resistance(resistance, res_array);
	printf("Antal komponenter som behövdes = %d\n", replacements);

//	minnesfrigöring
	free(res_array);

	return 0;
}

//@Param int returnerar korrekt pow
int upphojtTill (float orig_resistance) {
	int upphojtTill = 0;
	if (orig_resistance > 0.1) {
		double logUpphojtTill = log10(orig_resistance);
		upphojtTill = (int)logUpphojtTill;
	}
	return upphojtTill;
}

//@Param int returnerar korrekt siffra närmst men under resistans
float findNearest(float orig_resistance, float list[12]) {
    for (int i = 11; i >= 0; i--) {
        if (orig_resistance >= list[i]){                
            return list[i];
        }
    }
}

int e_resistance(float orig_resistance, float *res_array) {
    
    float E12_list[12] = {1.00, 1.20, 1.50, 1.80, 2.20, 2.70, 3.30, 3.90, 4.70, 5.60, 6.80, 8.20};
    
    float* resistorer = malloc (3 * sizeof(float));
    for (int i = 0; i < 4; i++) {
        resistorer[i] = 0;
    }
    
    int decade = 0;
    int i = 0;
    
    while (orig_resistance > 0 && i < 3) {    
    
        decade = upphojtTill(orig_resistance);
        float* nyLista = malloc(12 * sizeof(float));
        for (int i = 0; i < 12; i++) {
        	if (orig_resistance >= 1) {
            		nyLista[i] = round((E12_list[i] * pow(10, (double)decade))*1000.0)/1000.0;
          	} else {
            		if (orig_resistance >= 0.1) {
            			nyLista[i] = E12_list[i]/10;            		
            		} else if (orig_resistance >= 0.01) {
            			nyLista[i] = E12_list[i]/pow(10, 2);
    			} else if (orig_resistance >= 0.001) {
    				nyLista[i] = E12_list[i]/pow(10, 3);
    		}
            }
        	
        }
        
        float firstNearest = findNearest(orig_resistance, nyLista);
        
        resistorer[i] = firstNearest;
        orig_resistance -= firstNearest;
        i++;
        free(nyLista);
    }
    
    res_array = resistorer;
    printf("%.4f\n", (*(res_array)));
    printf("%.4f\n", (*(res_array + 1)));
    printf("%.4f\n", (*(res_array + 2)));
    free(resistorer);
    return (i);
}

float calc_power_i(float u, float i)
{
	return u * i;
}

float calc_power_r(float u, float r)
{
	return (u*u) / r;
}

float calc_resistance(int count, char conn, float *array){

	float resistance;

	if (conn == 'S' || conn == 's'){
 		for(int i = 0; i < count; i++){
			resistance += array[i];
		}
	} else if (conn == 'P' || conn == 'p'){
		float resBuffert = 0;

		for(int i = 0; i < count; i++){
			resBuffert += (1/array[i]);
			if(array[i] == 0){
				return 0;
			}
		}
		resistance = 1/resBuffert;
	} else {
		return -1;
	}

	return resistance;

}
