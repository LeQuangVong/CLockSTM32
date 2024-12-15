/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "i2c_lcd.h"
#include "stdio.h"
#include "DS3231.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
TIME time;
/* USER CODE BEGIN PV */
int congtru_tong = 0;
int congtru_menu1 = 0;
int demmenu1 = 0;
int contro = 0;
int congtru_menubaothuc = 0;
int contro_bt = 6;
int hang = 0;
int gtlen,gtxuong,gtmenu;
int demtong = 0;
int dembaothuc = 0;
int macdinh = 1;
char buffer[20];
int ngay = 1; int thang = 1; int namng = 0; int namtr = 0; int namch = 0; int namdv = 0; int namtong = 0; //SETUP DATE
int gio = 0; int phut = 0; int giay = 0; //SETUP TIME
int gio1 = 0; int phut1 = 0; int ngay1 = 1; int thang1 = 1; //BÁO TH?C 1
int gio2 = 0; int phut2 = 0; int ngay2 = 1; int thang2 = 1; //BÁO TH?C 2
int gio3 = 0; int phut3 = 0; int ngay3 = 1; int thang3 = 1; //BÁO TH?C 3
int gio4 = 0; int phut4 = 0; int ngay4 = 1; int thang4 = 1; //BÁO TH?C 4
int gio5 = 0; int phut5 = 0; int ngay5 = 1; int thang5 = 1; //BÁO TH?C 5
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void ManHinhChinh(void);
void MenuTong(void);
void Menu1(void);
void chonmenu_1(void);
void chonmenu_tong(void);
void menu_baothuc(void);
void chonmenu_baothuc(void);
void tru_ngay_gio(int *ngay, int *gio);
void tru_thang_phut(int *thang, int *phut);
void cong_ngay_gio(int *ngay, int *gio);
void cong_thang_phut(int *thang, int *phut);
void hien_thi_bt(int *ngay, int *thang, int *gio, int *phut);
void tb_baothuc(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	LCD_Init(2);
	//Set_Time(00,35,13,5,3,1,19);
	//ManHinhChinh();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		Get_Time();
		if (demtong == 0 && congtru_tong == 0 && dembaothuc == 0) // MÀN HÌNH
		{
			ManHinhChinh();
			LCD_NoCursor();
		}
		
		else if ((demtong == 2 || demtong == 3) && congtru_tong != 3) //Hi?n th? SETUP DATE or TIME
		{

			if(congtru_tong == 1) // SET DATE
			{
				if (ngay < 10)
				{
					LCD_SetCursor(0,1); LCD_PrintStr("0");
					sprintf(buffer, "%d", ngay);
					LCD_SetCursor(1,1); LCD_PrintStr(buffer);
				} 
				else 
				{
					sprintf(buffer, "%d", ngay);
					LCD_SetCursor(0,1); LCD_PrintStr(buffer);    
				}
    
				LCD_SetCursor(2,1); LCD_PrintStr("/");
    
				if (thang < 10)
				{
					LCD_SetCursor(3,1); LCD_PrintStr("0"); 
					sprintf(buffer, "%d", thang);
					LCD_SetCursor(4,1); LCD_PrintStr(buffer);
				} 
				else 
				{
					sprintf(buffer, "%d", thang);
					LCD_SetCursor(3,1); LCD_PrintStr(buffer);    
				}
    
				LCD_SetCursor(5,1); LCD_PrintStr("/"); 
    
				sprintf(buffer, "%d", namng);
				LCD_SetCursor(6,1); LCD_PrintStr(buffer);
				sprintf(buffer, "%d", namtr);
				LCD_SetCursor(7,1); LCD_PrintStr(buffer);
				sprintf(buffer, "%d", namch);
				LCD_SetCursor(8,1); LCD_PrintStr(buffer);
				sprintf(buffer, "%d", namdv);
				LCD_SetCursor(9,1); LCD_PrintStr(buffer);
    
				namtong = /*(namng * 1000) + (namtr * 100) + */(namch * 10) + namdv;

				LCD_SetCursor(contro, 1); 
				LCD_Cursor();
				HAL_Delay(50);  

				Set_Date(ngay, thang, namtong);
			}
			else if (congtru_tong == 2) // SET TIME
			{
				if (gio < 10)
				{
					LCD_SetCursor(0,1); LCD_PrintStr("0");
					sprintf(buffer, "%d", gio);
					LCD_SetCursor(1,1); LCD_PrintStr(buffer);
				} 
				else 
				{
					sprintf(buffer, "%d", gio);
					LCD_SetCursor(0,1); LCD_PrintStr(buffer);
				}
			
				LCD_SetCursor(2,1); LCD_PrintStr(":");
			
				if (phut < 10)
				{
					LCD_SetCursor(3,1); LCD_PrintStr("0"); 
					sprintf(buffer, "%d", phut);
					LCD_SetCursor(4,1); LCD_PrintStr(buffer);
				} 
				else 
				{
					sprintf(buffer, "%d", phut);
					LCD_SetCursor(3,1); LCD_PrintStr(buffer);    
				}  
			
				LCD_SetCursor(5,1); LCD_PrintStr(":");
			
				if (giay < 10)
				{
					LCD_SetCursor(6,1); LCD_PrintStr("0"); 
					sprintf(buffer, "%d", giay);
					LCD_SetCursor(7,1); LCD_PrintStr(buffer);
				} 
				else 
				{
					sprintf(buffer, "%d", giay);
					LCD_SetCursor(6,1); LCD_PrintStr(buffer);  
				}
			}


			LCD_SetCursor(contro, 1); 
			LCD_Cursor();
			HAL_Delay(50);

			Set_Time(giay, phut, gio); 
		}
		else if ((demtong == 3 || demtong == 4) && congtru_tong == 3) //Hi?n th? SETUP BÁO TH?C
{
  if(congtru_menubaothuc == 1) //BT 1
    hien_thi_bt(&ngay1, &thang1, &gio1, &phut1);  
  else if(congtru_menubaothuc == 2) //BT 2
    hien_thi_bt(&ngay2, &thang2, &gio2, &phut2);  
  else if(congtru_menubaothuc == 3) //BT 3
    hien_thi_bt(&ngay3, &thang3, &gio3, &phut3);  
  else if(congtru_menubaothuc == 4) //BT 4
    hien_thi_bt(&ngay4, &thang4, &gio4, &phut4);                    
  else if(congtru_menubaothuc == 5) //BT 5
    hien_thi_bt(&ngay5, &thang5, &gio5, &phut5);      
}

if (demtong == 0){ // CH? KHI ? MÀN HÌNH CHÍNH M?I HI?N BÁO TH?C
  // Th?c thi BÁO TH?C
  if ((time.day == ngay1 || time.day == ngay2 || time.day == ngay3 || time.day == ngay4 || time.date == ngay5) && 
      (time.month == thang1 || time.month == thang2 || time.month == thang3 || time.month == thang4 || time.month == thang5) && 
      (time.hour == gio1 || time.hour == gio2 || time.hour == gio3 || time.hour == gio4 || time.hour == gio5) && 
      (time.min == phut1 || time.min == phut2 || time.min == phut3 || time.min == phut4 || time.min == phut5) && time.sec == 1)      
  { dembaothuc = 1; }
} else dembaothuc = 0; // N?U ÐANG ? CÁC MENU HAY SETUP THÌ KHÔNG BÁO TH?C

if (dembaothuc == 1){
  tb_baothuc();
}

		if (HAL_GPIO_ReadPin(BUTTON2_GPIO_Port,BUTTON2_Pin)== 0) // Khi nh?n nút lên
		{
			while(HAL_GPIO_ReadPin(BUTTON2_GPIO_Port,BUTTON2_Pin) == 0){}
			if (demtong == 1)   // LÊN ? MENU T?NG  
			{
				if (congtru_tong >= 5)
				{ 
					congtru_tong = 0;  
				}
				else
				{ 
					congtru_tong++;  
				}   
				MenuTong();
			}
			else if (demtong == 2 && (congtru_tong == 1 || congtru_tong == 2))   // + CON TR? ? SET DATE và TIME
			{
				contro ++;
				if (contro > 15)
					contro = 0;
			}
			else if (demtong == 3) // - ? ngày, tháng, nam, gi?, phút, giây và + con tr? Báo Th?c   
    {
      if(congtru_tong == 1) // - ? NGÀY, THÁNG, NAM
      {
        if ((contro == 0 || contro == 1)){ //NGÀY
          ngay --;
          if (ngay < 1)
            ngay = 31;
        }
        else if ((contro == 3 || contro == 4)){ //THÁNG
          thang --;
          if (thang < 1)
            thang = 12;
        }

          else if (contro == 6){ //NAM NGHÌN
            namng --;
            if (namng < 0)
              namng = 9;
          }
          else if (contro == 7){ //NAM TRAM
            namtr --;
            if (namtr < 0)
              namtr = 9;
          }
          else if (contro == 8){ //NAM CH?C
            namch --;
            if (namch < 0)
              namch = 9;
          }
          else if (contro == 9){ //NAM ÐON V?
            namdv --;
            if (namdv < 0)
              namdv = 9;
          }
      }
      else if (congtru_tong == 2) // - ? GI? : PHÚT : GIÂY
      {
        if ((contro == 0 || contro == 1)){ //GI?
          gio --;
          if (gio < 0)
            gio = 23;
        }
        else if ((contro == 3 || contro == 4)){ //PHÚT
          phut --;
          if (phut < 0)
            phut = 59;
        }
        else if ((contro == 6 || contro == 7)){ //GIÂY
          giay --;
          if (giay < 0)
            giay = 59;  
        }
      }
      else if (congtru_tong == 3) // + CON TR? ? BÁO TH?C
      {
        contro_bt ++;
        if (hang == 0){
          if (contro_bt > 10)
          { contro_bt = 6;
            hang = 1; }
        } else {
          if (contro_bt > 15)
          { contro_bt = 6;
            hang = 0; }       
        }
      }
		}
			else if (demtong == 2 && congtru_tong == 3) //Lên ? MENU BÁO TH?C
    {
      congtru_menubaothuc++;
      if (congtru_menubaothuc > 5)
        {congtru_menubaothuc = 0;}
      menu_baothuc();
    }
		
			else if (demtong == 4 && congtru_tong == 3) // - BÁO TH?C | NGÀY/THÁNG & GI?/PHÚT
    {
      if(contro_bt == 6 || contro_bt == 7) // Ngày or Gi?
      {
        if (congtru_menubaothuc == 1) // - NGÀY & GI? 1
          tru_ngay_gio(&ngay1, &gio1);
        else if (congtru_menubaothuc == 2) // - NGÀY & GI? 2
          tru_ngay_gio(&ngay2, &gio2); 
        else if (congtru_menubaothuc == 3) // - NGÀY & GI? 3
          tru_ngay_gio(&ngay3, &gio3); 
        else if (congtru_menubaothuc == 4) // - NGÀY & GI? 4
          tru_ngay_gio(&ngay4, &gio4); 
        else if (congtru_menubaothuc == 5) // - NGÀY & GI? 5
          tru_ngay_gio(&ngay5, &gio5);                                      
      }
      else if (contro_bt == 9 || contro_bt == 10) // Tháng or phút
      {
        if (congtru_menubaothuc == 1) // - THÁNG & PHÚT 1
          tru_thang_phut(&thang1, &phut1);
        else if (congtru_menubaothuc == 2) // - THÁNG & PHÚT 2
          tru_thang_phut(&thang2, &phut2);
        else if (congtru_menubaothuc == 3) // - THÁNG & PHÚT 3
          tru_thang_phut(&thang3, &phut3);
        else if (congtru_menubaothuc == 4) // - THÁNG & PHÚT 4
          tru_thang_phut(&thang4, &phut4);
        else if (congtru_menubaothuc == 5) // - THÁNG & PHÚT 5
          tru_thang_phut(&thang5, &phut5);                              
      }
    }     
  }
		
		if (HAL_GPIO_ReadPin(BUTTON3_GPIO_Port,BUTTON3_Pin) != macdinh)
		{
			if (HAL_GPIO_ReadPin(BUTTON3_GPIO_Port,BUTTON3_Pin)== 0) // Khi nh?n nút lên
			{
				while(HAL_GPIO_ReadPin(BUTTON3_GPIO_Port,BUTTON3_Pin) == 0){}
				if (demtong == 1)   // LÊN ? MENU T?NG  
				{
					if (congtru_tong <= 0)
					{ 
						congtru_tong = 5;  
					}
					else
					{ 
						congtru_tong--;  
					}   
					MenuTong();
				}
				else if (demtong == 2 && (congtru_tong == 1 || congtru_tong == 2))   // - CON TR? ? SET DATE và TIME
				{
					contro --;
					if (contro < 0)
					{
						contro = 15;
					}
				}
				else if (demtong == 3) // + ? Ngày, tháng, nam, gi?, phút, giây và - con tr? Báo Th?c
				{
					if(congtru_tong == 1) // + ? NGÀY, THÁNG, NAM
					{
						if (contro == 0 || contro == 1){ // + NGÀY ? DATE
							ngay ++;
							if (ngay > 31)
								ngay = 1; }
						else if (contro == 3 || contro == 4){ // + THÁNG ? DATE
							thang ++;
							if (thang > 12)
								thang = 1; }
						else if (contro == 6){ // + NAM NGHÌN
							namng ++;
							if (namng > 9)
								namng = 0; }
						else if (contro == 7){// + NAM TRAM
							namtr ++;
							if (namtr > 9)
								namtr = 0; }
						else if (contro == 8){// + NAM CH?C
							namch ++;
							if (namch > 9)
								namch = 0; }
						else if (contro == 9){// + NAM ÐON V?
							namdv ++;
							if (namdv > 9)
								namdv = 0; }
					}
					else if(congtru_tong == 2) //+ ? GI? : PHÚT :GIÂY
					{
						if (contro == 0 || contro == 1){ //GI?
							gio ++;
							if (gio > 23)
								gio = 0;     }

						else if (contro == 3 || contro == 4){ //PHÚT
							phut ++;
							if (phut > 59)
								phut = 0;  }

						else if (contro == 6 || contro == 7){ //GIÂY
							giay ++;
							if (giay > 59)
								giay = 0;  }
					}
					else if(congtru_tong == 3) // - CON TR? ? BÁO TH?C
					{
						contro_bt--;
						if (hang == 0){
							if (contro_bt < 6)
							{ contro_bt = 15;
								hang = 1; }
						} else {
							if (contro_bt < 6)
							{ contro_bt = 10;
								hang = 0; }        
						} 
					}
				}
				else if (demtong == 2 && congtru_tong == 3) //Xu?ng ? MENU BÁO TH?C
				{
					congtru_menubaothuc --;
					if (congtru_menubaothuc < 0)
						{congtru_menubaothuc = 5;}
					menu_baothuc();
				}
				else if (demtong == 4 && congtru_tong == 3) // - BÁO TH?C | NGÀY/THÁNG & GI?/PHÚT
				{
					if(contro_bt == 6 || contro_bt == 7) // Ngày or Gi?
					{
						if (congtru_menubaothuc == 1) // - NGÀY & GI? 1
							cong_ngay_gio(&ngay1, &gio1);
						else if (congtru_menubaothuc == 2) // - NGÀY & GI? 2
							cong_ngay_gio(&ngay2, &gio2); 
						else if (congtru_menubaothuc == 3) // - NGÀY & GI? 3
							cong_ngay_gio(&ngay3, &gio3); 
						else if (congtru_menubaothuc == 4) // - NGÀY & GI? 4
							cong_ngay_gio(&ngay4, &gio4); 
						else if (congtru_menubaothuc == 5) // - NGÀY & GI? 5
							cong_ngay_gio(&ngay5, &gio5);                                      
					}
					else if (contro_bt == 9 || contro_bt == 10) // Tháng or phút
					{
						if (congtru_menubaothuc == 1) // - THÁNG & PHÚT 1
							cong_thang_phut(&thang1, &phut1);
						else if (congtru_menubaothuc == 2) // - THÁNG & PHÚT 2
							cong_thang_phut(&thang2, &phut2);
						else if (congtru_menubaothuc == 3) // - THÁNG & PHÚT 3
							cong_thang_phut(&thang3, &phut3);
						else if (congtru_menubaothuc == 4) // - THÁNG & PHÚT 4
							cong_thang_phut(&thang4, &phut4);
						else if (congtru_menubaothuc == 5) // - THÁNG & PHÚT 5
							cong_thang_phut(&thang5, &phut5);                              
					}
				}
    }
	}
	
		if (HAL_GPIO_ReadPin(BUTTON1_GPIO_Port,BUTTON1_Pin) != macdinh)    // NÚT MENU
		{  
			if (HAL_GPIO_ReadPin(BUTTON1_GPIO_Port,BUTTON1_Pin) == 0) //Khi nh?n nút
			{  
				while(HAL_GPIO_ReadPin(BUTTON1_GPIO_Port,BUTTON1_Pin) == 0){}
				demtong ++;

				if (demtong == 1) //? menu t?ng
				{ 
					MenuTong(); 
				}
				else if (demtong == 2)
				{					//Nh?n BACK t? Menu t?ng v? màn hình
					if(congtru_tong == 0)
					{
						demtong = 0;
						ManHinhChinh(); 
					}
					else if(congtru_tong == 1 || congtru_tong == 2) // ch?n menu t?ng DATE or TIME
						chonmenu_tong();
					else if(congtru_tong == 3) //Menu BÁO TH?C
					menu_baothuc();
				}
				else if (demtong == 4) //Thoát CON TR? t? SET DATE or TIME ra
				{
					if (congtru_tong == 1) //Thoát CON TR? t? SET DATE ra
					{ 
						demtong = 2;
						chonmenu_tong(); 
					}
					else if (congtru_tong == 2) //Thoát CON TR? t? SET TIME ra
					{ 
						demtong = 2;
						chonmenu_tong();
					}
					else if (congtru_tong == 3 && (contro_bt == 12 || contro_bt == 13 || contro_bt == 14 || contro_bt == 15)) //Thoát t? SET BT ra menu báo th?c
					{
						menu_baothuc();
						demtong = 2;
						congtru_tong = 3;
						contro_bt = 6;
						hang = 0;
						LCD_NoCursor();
					}
				}
				
				else if (demtong == 3 && (congtru_tong == 2 || congtru_tong == 1) && // Thoát t? SET DATE or TIME ra
            (contro == 12 || contro == 13 || contro == 14 || contro == 15)) 
					{
						demtong = 1;
						congtru_tong = 0;
						contro = 0;
						MenuTong();
						LCD_NoCursor();
					}
					
					 else if (demtong == 3 && congtru_tong == 3) //Ch?n MENU Báo Th?c 
      {
        if(congtru_menubaothuc == 0){ //t? Menu BÁO TH?C v? Menu T?NG
          demtong = 1;
          congtru_menubaothuc = 0;
          MenuTong();}

        else if(congtru_menubaothuc == 1 || congtru_menubaothuc == 2 || congtru_menubaothuc == 3 
                || congtru_menubaothuc == 4 || congtru_menubaothuc == 5) //ch?n menu BT
        {
          chonmenu_baothuc();
        }
      }

    else if (demtong == 5 && congtru_tong == 3 && (congtru_menubaothuc == 1 || congtru_menubaothuc == 2
            || congtru_menubaothuc == 3 || congtru_menubaothuc == 4 || congtru_menubaothuc == 5))  //T? ch?c nang SET ra
      {
        chonmenu_baothuc();
        demtong = 3;
      }

    if(dembaothuc == 1){ //Ðang có BÁO TH?C
      dembaothuc = 0;
      demtong = 0; }
			}
		}	
	}
  /* USER CODE END 3 */
}



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : BUTTON1_Pin BUTTON2_Pin BUTTON3_Pin */
  GPIO_InitStruct.Pin = BUTTON1_Pin|BUTTON2_Pin|BUTTON3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void ManHinhChinh(void)
{
	//LCD_Clear();
	sprintf (buffer, "%02d:%02d:%02d", time.hour,time.min,time.sec);
	LCD_SetCursor(0,0);
	LCD_PrintStr(buffer);

	sprintf (buffer, "%02d-%02d-20%02d", time.day, time.month, time.year);
	LCD_SetCursor(0,1);
	LCD_PrintStr(buffer);
	HAL_Delay(500);
}

void MenuTong(void)
{
	if (congtru_tong == 0)
  {
    LCD_Clear();
		LCD_SetCursor(0,0);
		LCD_PrintStr(">BACK");
    LCD_SetCursor(0,1);
    LCD_PrintStr(" DATE");  
  }
	else if (congtru_tong == 1)
  {
    LCD_Clear();
		LCD_SetCursor(0,0);
		LCD_PrintStr(" BACK");
    LCD_SetCursor(0,1);
    LCD_PrintStr(">DATE");  
  }
	else if (congtru_tong == 2)
  {
    LCD_Clear();
		LCD_SetCursor(0,0);
		LCD_PrintStr(">TIME");
    LCD_SetCursor(0,1);
    LCD_PrintStr(" ALARM");  
  }
	else if (congtru_tong == 3)
  {
    LCD_Clear();
		LCD_SetCursor(0,0);
		LCD_PrintStr(" TIME");
    LCD_SetCursor(0,1);
    LCD_PrintStr(">ALARM");  
  }
}

void chonmenu_tong(void) // CH?N MENU T?NG
{
  switch (congtru_tong) 
  {
    case 0:
      //BACK
      break;
    case 1:
      LCD_Clear();
      LCD_SetCursor(0,0);
      LCD_PrintStr("SETUP DATE");
      LCD_SetCursor(12,1);
      LCD_PrintStr("BACK");      
      break;
    case 2:
      LCD_Clear();
      LCD_SetCursor(0,0);
      LCD_PrintStr("SETUP TIME");
      LCD_SetCursor(12,1);
      LCD_PrintStr("BACK");       
      break;
    case 3:
      // BÁO TH?C
      break;                       
  }
}

void menu_baothuc(void) // HI?N TH? MENU BÁO TH?C
{
  if (congtru_menubaothuc == 0)
  {
    LCD_Clear();
		LCD_SetCursor(0,0);
    LCD_PrintStr(">BACK");
    LCD_SetCursor(0, 1);
    LCD_PrintStr(" BAO THUC 1");  
  }
  else if (congtru_menubaothuc == 1)
  {
    LCD_Clear();
		LCD_SetCursor(0,0);
    LCD_PrintStr(" BACK");
    LCD_SetCursor(0, 1);
    LCD_PrintStr(">BAO THUC 1");     
  }
  else if (congtru_menubaothuc == 2)
  {
    LCD_Clear();
		LCD_SetCursor(0,0);
    LCD_PrintStr(" BAO THUC 1");
    LCD_SetCursor(0, 1);
    LCD_PrintStr(">BAO THUC 2");   
  } 
  else if (congtru_menubaothuc == 3)
  {
    LCD_Clear();
		LCD_SetCursor(0,0);
    LCD_PrintStr(" BAO THUC 2");
    LCD_SetCursor(0, 1);
    LCD_PrintStr(">BAO THUC 3"); 
  } 
  else if (congtru_menubaothuc == 4)
  {
    LCD_Clear();
		LCD_SetCursor(0,0);
    LCD_PrintStr(">BAO THUC 4");
    LCD_SetCursor(0, 1);
    LCD_PrintStr(" BAO THUC 5");    
  } 
  else if (congtru_menubaothuc == 5)
  {
    LCD_Clear();
		LCD_SetCursor(0,0);
    LCD_PrintStr(" BAO THUC 4");
    LCD_SetCursor(0, 1);
    LCD_PrintStr(">BAO THUC 5");     
  }        
}

void chonmenu_baothuc(void) // CH?N MENU BÁO TH?C
{
  switch (congtru_menubaothuc) 
  {
    case 0:
      //BACK
      break;
    case 1:
      LCD_Clear();
      LCD_SetCursor(0,0);
      LCD_PrintStr("DATE: ");
      LCD_SetCursor(0,1);
      LCD_PrintStr("TIME: ");
      LCD_SetCursor(12,1);
      LCD_PrintStr("BACK");
      break;
    case 2:
      LCD_Clear();
      LCD_SetCursor(0,0);
      LCD_PrintStr("DATE: ");
      LCD_SetCursor(0,1);
      LCD_PrintStr("TIME: ");
      LCD_SetCursor(12,1);
      LCD_PrintStr("BACK");     
      break;
    case 3:
      LCD_Clear();
      LCD_SetCursor(0,0);
      LCD_PrintStr("DATE: ");
      LCD_SetCursor(0,1);
      LCD_PrintStr("TIME: ");
      LCD_SetCursor(12,1);
      LCD_PrintStr("BACK");    
      break;
    case 4:
      LCD_Clear();
      LCD_SetCursor(0,0);
      LCD_PrintStr("DATE: ");
      LCD_SetCursor(0,1);
      LCD_PrintStr("TIME: ");
      LCD_SetCursor(12,1);
      LCD_PrintStr("BACK");      
      break;
    case 5:
      LCD_Clear();
      LCD_SetCursor(0,0);
      LCD_PrintStr("DATE: ");
      LCD_SetCursor(0,1);
      LCD_PrintStr("TIME: ");
      LCD_SetCursor(12,1);
      LCD_PrintStr("BACK");       
      break;                             
  }
}




void tru_ngay_gio(int *ngay, int *gio)
{
  if (hang == 0){ // - NGÀY
    (*ngay)--;
    if ((*ngay)< 1)
      (*ngay) = 31; } 
  else if (hang == 1){ // - GI?
    (*gio)--;
    if ((*gio) < 0)
      (*gio) = 23; }  
}
void tru_thang_phut(int *thang, int *phut)
{
  if (hang == 0){ // - THÁNG
    (*thang)--;
    if ((*thang) < 1)
      (*thang) = 12; } 
  else if (hang == 1){  // - PHÚT
    (*phut)--;
    if ((*phut) < 0)
      (*phut) = 59; }  
}
void cong_ngay_gio(int *ngay, int *gio)
{
  if (hang == 0){ // + NGÀY
    (*ngay)++;
    if ((*ngay) > 31)
      (*ngay) = 1;  } 
  else if (hang == 1){ // + GI?
    (*gio)++;
    if ((*gio) > 23)
      (*gio) = 0; }  
}
void cong_thang_phut(int *thang, int *phut)
{
  if (hang == 0){ // + THÁNG
    (*thang)++;
    if ((*thang) > 12)
      (*thang) = 1; } 
  else if (hang == 1){ // + PHÚT
    (*phut)++;
    if ((*phut) > 59)
      (*phut) = 0; }  
}
void hien_thi_bt(int *ngay, int *thang, int *gio, int *phut)
{
  // Hi?n th? ngày
  if (*ngay < 10) {
    LCD_SetCursor(6, 0); LCD_PrintStr("0");
    sprintf(buffer, "%d", *ngay);
    LCD_SetCursor(7, 0); LCD_PrintStr(buffer);
  } else {
    sprintf(buffer, "%d", *ngay);
    LCD_SetCursor(6, 0); LCD_PrintStr(buffer);
  }

  LCD_SetCursor(8, 0); LCD_PrintStr("/");

  // Hi?n th? tháng
  if (*thang < 10) {
    LCD_SetCursor(9, 0); LCD_PrintStr("0");
    sprintf(buffer, "%d", *thang);
    LCD_SetCursor(10, 0); LCD_PrintStr(buffer);
  } else {
    sprintf(buffer, "%d", *thang);
    LCD_SetCursor(9, 0); LCD_PrintStr(buffer);
  }

  LCD_SetCursor(11, 0); LCD_PrintStr("/");

  // Hi?n th? gi?
  if (*gio < 10) {
    LCD_SetCursor(6, 1); LCD_PrintStr("0");
    sprintf(buffer, "%d", *gio);
    LCD_SetCursor(7, 1); LCD_PrintStr(buffer);
  } else {
    sprintf(buffer, "%d", *gio);
    LCD_SetCursor(6, 1); LCD_PrintStr(buffer);
  }

  LCD_SetCursor(8, 1); LCD_PrintStr(":");

  // Hi?n th? phút
  if (*phut < 10) {
    LCD_SetCursor(9, 1); LCD_PrintStr("0");
    sprintf(buffer, "%d", *phut);
    LCD_SetCursor(10, 1); LCD_PrintStr(buffer);
  } else {
    sprintf(buffer, "%d", *phut);
    LCD_SetCursor(9, 1); LCD_PrintStr(buffer);
  }    

  LCD_SetCursor(contro_bt, hang); 
  LCD_Cursor();
  HAL_Delay(50);
}

void tb_baothuc(void)
{
  LCD_Clear();
  LCD_SetCursor(3,0);
  LCD_PrintStr("THONG BAO");
  LCD_SetCursor(2,1);
  LCD_PrintStr("CO BAO THUC");  
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
