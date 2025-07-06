#include "Mask_perform.h"


int Mask_performassignment(CAR *car, MASK_ASSIGNMENT assignment)
{
	  switch(assignment)
		{
			case wait_start:
					return Car_waitstartfuc(car);
					break;
			case goto_line:
				  return Car_gotolinefuc(car);
					break;
			case goto_turnright:
				  return Car_gototurnrightfuc(car);
					break;
			case goto_turnleft:
				  return Car_gototurnleftfuc(car);
					break;
			case go_strightoverflow:
					return Car_gostrightoverflowfuc(car);
					break;
			case turnright:
					return Car_turnrightfuc(car);
					break;
			case turnleft:
					return Car_turnleftfuc(car);
					break;
			case beep:
					return Car_beepfuc(car);
					break;
			case stop:
					return Car_stopfuc(car);
					break;
			case go_avoidance:
				  return Car_goavoidance(car);
				  break;
			case gobackto_line:
				  return Car_gobacktolinefuc(car);
				  break;
			case goto_allwhite:
				  return Car_gotoallwhitefuc(car);
				  break;
			case getnum:
				  return Car_getnumberfuc(car);
				  break;
			case turnleftto_line:
				  return Car_turnlefttolinefuc(car);
				  break;
			case gountil_end:
				  return Car_gountilend(car);
				  break;
			case turnto_end:
				  return Car_turntoend(car);
				  break;
			case resethwt101:
					return Car_resethwt101fuc(car);
				  break;		
			case voice_trace:
					return Car_voicetrance(car);
				  break;		
			default:
					return Car_stopfuc(car);
			    break;
				
		}

}

void Mask_setassignments(CAR*car,MASK_ASSIGNMENT* assignments,int assignments_num)
{
  for(int j = 0;j < assignments_num;j++)
	{
	  car->mask_assignment[j] = assignments[j];
	}
}

void Mask_performassignments(CAR *car,int mask_num)
{
	static int cnt = 0;
	if(cnt < mask_num)
	 {
		 int i = Mask_performassignment(car,car->mask_assignment[cnt]);
		  cnt = cnt + i;
	 }
	else
	 {
	   Mask_performassignment(car,stop);
	 }		
}



