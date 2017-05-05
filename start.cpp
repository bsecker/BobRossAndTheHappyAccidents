
/* Tryig remote compilig on RPI */

#include <stdio.h>
#include <unistd.h>
#include "camera.h"
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pigpio.h>

#define CAMERA_WIDTH 320 //Control Resolution from Camera
#define CAMERA_HEIGHT 240 //Control Resolution from Camera
#define FB_MAX_SIZE 5000000

// camera stuff
CCamera *cam;  // camera instance
int  Y_row[CAMERA_WIDTH];
char pixels_buf[CAMERA_WIDTH*CAMERA_HEIGHT*4];

int disp_level = 0;

// camera image converted to fit display depth - somewhat big for 1960x1050 screen
char cam_disp[FB_MAX_SIZE];
// original image on the screen
char original[FB_MAX_SIZE];
int fbfd = 0;
struct fb_var_screeninfo orig_vinfo;
char *fbp = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
long int screensize;
int res;
// hardware
int spi_h; // handle of SPI
int sock;  // socket handle

/**********ESSWENTIAL*******/

void stop(int)
{
	printf("stop called\n");
    gpioPWM(16,0);
    gpioPWM(12,0);
    gpioPWM(20,0);
    gpioPWM(21,0);
	gpioTerminate();
}

int init()
{
	// stop on Ctrl_C
    signal(2,stop);

	cam = StartCamera(CAMERA_WIDTH, CAMERA_HEIGHT,70,1,true);
    if (cam == NULL)
    {
        printf(" Camera initialization failure\n");
        return -2;
    }
    if (gpioInitialise() < 0)
    {
      printf("GPIO initialization failed \n");
      return -1;
    }
    //gpioSetMode(24,PI_OUTPUT);

    // set motor pins
    gpioSetMode(12,PI_OUTPUT);
    gpioSetMode(16,PI_OUTPUT);
    gpioSetMode(20,PI_OUTPUT);
    gpioSetMode(21,PI_OUTPUT);
    gpioSetPWMfrequency(12,500);
    gpioSetPWMfrequency(16,500);
    gpioSetPWMfrequency(20,500);
    gpioSetPWMfrequency(21,500);
    // initialize ADC inteface
    spi_h = spiOpen(0,5000,0);
    if (spi_h<0)
    {
        printf("SPI failure\n");
        return -3;
    }
    // success
    // give camera time to settle
    sleep(1);
    
    return 0;
}





/*******CAMERA FUNCTIONS****************/

// takes camera picture and stores it into mybuff
int take_picture()
{
   if (disp_level>0)
   {
      printf("Taking camera picture\n");
   }
   cam->ReadFrame(0,&(pixels_buf[0]),sizeof(pixels_buf));
   usleep(10000);  //just in case
   if (disp_level>0)
   {
      printf("Picture taken\n");
   }

   return 0;
}

int save_picture(char fn[5])
{
          //save image into ppm file
        FILE *fp;
        char fname[9];
        sprintf(fname,"%s.ppm",fn);
        if (disp_level>0)
        {
           printf("Saving picture. %s\n",fname);
        }
        fp = fopen(fname,"wb");
        if ( !fp)
        {
           printf("Unable to open the file\n");
           return -1;
        }
        // write file header
        fprintf(fp,"P6\n %d %d %d\n",CAMERA_WIDTH , CAMERA_HEIGHT,255);
        int ind = 0;
        int row = 0;
        int col = 0;
        char red;
        char green;
        char blue;
        for ( row = 0 ; row < CAMERA_HEIGHT; row++)
        {
           for ( col = 0 ; col < CAMERA_WIDTH; col++)
           {
		     red =  pixels_buf[ind];
		     green =  pixels_buf[ind+1];
		     blue =  pixels_buf[ind+2];
		     fprintf(fp,"%c%c%c",red,green,blue);
		     ind = ind + 4;
           }
        }
        fflush(fp);
        fclose(fp);
        //system("timeout 1s gpicview im1.ppm");
        return 0;

}


// returns color component (color==0 -red,color==1-green,color==2-blue
// color == 3 - luminocity
// for pixel located at
unsigned char get_pixel( int row,int col, int color)
{
    // calculate address in 1D array of pixels
    int address = CAMERA_WIDTH*row*4 + col*4;
    if ((row < 0 ) || (row > CAMERA_HEIGHT) )
    {
        printf("row is out of range\n");
        return -1;
    }
    if ( (col< 0) || (col > CAMERA_WIDTH))
    {
        printf("column is out of range\n");
        return -1;
    }


    if (color==0)
    {
        return (pixels_buf[address]);
    }
    if (color==1)
    {
        return (pixels_buf[address + 1]);
    }
    if (color==2)
    {
        return (pixels_buf[address + 2]);
    }
    if (color==3)
    {
        unsigned char y = (pixels_buf[address] + pixels_buf[address+1] +pixels_buf[address+2])/3;
        return y;
    }
    printf("Color encoding wrong: 0-red, 1-green,2-blue,3 - luminosity\n");
    return -2; //error
}

int set_pixel(int row, int col, char red, char green,char blue)
{
    int address = CAMERA_WIDTH*row*4 + col*4;
    if ((address < 0) || (address>CAMERA_WIDTH*CAMERA_HEIGHT*4))
    {
        printf("SetPixel(): wrong x,y coordinates\n");
        return -1;
    }
    pixels_buf[address] = red;
    pixels_buf[address+1] = green;
    pixels_buf[address+2] = blue;
    return 0;
}

// takes camera picture and converts it
// into format for frame buffer (2 Bytes per pixel)
// fill
void convert_camera_to_screen()
{
  int x;
  int y;
  int x_offset =10;
  int y_offset =10;
  // take snapshot of original screen
  memcpy(&(cam_disp[0]),fbp,screensize);
  for ( x = 0 ; x < CAMERA_WIDTH ; x++)
   {
      for ( y = 0 ; y < CAMERA_HEIGHT; y++)
       {
		  int r = get_pixel(y,x,0);
		  int g = get_pixel(y,x,1);
		  int b = get_pixel(y,x,2);
		  if (vinfo.bits_per_pixel == 16) {
                //put_pixel_RGB565(x+x_offset, y+y_offset, r, g, b);
                 // calculate the pixel's byte offset inside the buffer
                 // note: x * 2 as every pixel is 2 consecutive bytes
                 unsigned int pix_offset = (x+x_offset) * 2 +( y+y_offset) * finfo.line_length;
                 // now this is about the same as 'fbp[pix_offset] = value'
                 // but a bit more complicated for RGB565
                 //unsigned short c = ((r / 8) << 11) + ((g / 4) << 5) + (b / 8);
                 unsigned short c = ((r / 8) * 2048) + ((g / 4) * 32) + (b / 8);
                 // write 'two bytes at once'
                 *((unsigned short*)(cam_disp + pix_offset)) = c;
            }
            else {
                // calculate the pixel's byte offset inside the buffer
                // note: x * 3 as every pixel is 3 consecutive bytes
                unsigned int pix_offset = (x+x_offset) * 3 + (y+y_offset) * finfo.line_length;
                // now this is about the same as 'fbp[pix_offset] = value'
                 *((char*)(cam_disp + pix_offset)) = b;
                 *((char*)(cam_disp + pix_offset + 1)) = g;
                 *((char*)(cam_disp + pix_offset + 2)) = r;
                //put_pixel_RGB24(x+x_offset, y+y_offset, r, g, b);
            }
       }
    }

}


int open_screen_stream()
{
    //char *fbp = 0;
   //struct fb_var_screeninfo vinfo;
   //struct fb_fix_screeninfo finfo;

    fbfd = 0;
    //struct fb_var_screeninfo orig_vinfo;
    screensize = 0;
    res=-1;
    // camera image converted to fit display depth - somewhat big for 1960x1050 screen
    //char cam_disp[3528000];
    // original image on the screen
    //char original[3528000];

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
      printf("Error: cannot open framebuffer device: %s\n",strerror(errno));
      return(1);
    }
    if (disp_level>0)
    {
      printf("The framebuffer device was opened successfully.fbfd=%d\n",fbfd);
    }

    // Get variable screen information
    res = ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo);
    if (res == -1) {
      printf("Error reading variable information: %s\n",strerror(errno));
    }
    if (disp_level>0)
    {
      printf("Original %dx%d, %dbpp\n", vinfo.xres, vinfo.yres,
                                      vinfo.bits_per_pixel );
    }
    // Store for reset (copy vinfo to vinfo_orig)
    memcpy(&orig_vinfo, &vinfo, sizeof(struct fb_var_screeninfo));

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
      printf("Error reading fixed information.\n");
    }

    // map fb to user mem
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    if (disp_level>0)
    {
       printf("screensize=%ld\n",screensize);
    }
    if ( screensize>FB_MAX_SIZE)
    {
        printf("Not enough memory to store the screen\n");
        return -1;
    }
    fbp = (char*)mmap(0,
              screensize,
              PROT_READ | PROT_WRITE,
              MAP_SHARED,
              fbfd,
              0);

    if ((int)fbp == -1) {
        printf("Failed to mmap display.\n");
        return -1;
    }

    return 0;
}

int close_screen_stream()
{
   munmap(fbp, screensize);
   if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &orig_vinfo)) {
        printf("Error re-setting variable information.\n");
        return -1;
   }
   close(fbfd);
   return 0;
}

int update_screen()
{
   if ((int)fbp == -1) {
        printf("UpdateScreen() - no screen buffer handle\n");
        return -1;
   }
   //  memcpy(&(cam_disp[0]),fbp,screensize);
   // modify cam_disp with camera image
   convert_camera_to_screen(); //
    // copy original sceen fb to "original" buffer
   //memcpy(&(original[0]),fbp,screensize);
   // original screen -> cam_disp
   //memcpy(&(cam_disp[0]),fbp,screensize);
   // put cam_disp to screen
   memcpy(fbp,&(cam_disp[0]),screensize);
   usleep(3000);
   return 0;
}



int display_picture(int delay_sec,int delay_usec)
{
   open_screen_stream();
   if (disp_level>0)
   {
      printf("open_screen_stream() OK\n");
   }

   // copy original sceen fb to "original" buffer
   memcpy(&(original[0]),fbp,screensize);
   // original screen -> cam_disp
  // memcpy(&(cam_disp[0]),fbp,screensize);
   // update camera portion of the screen
   update_screen();
   if (disp_level>0)
   {
      printf("update_screen() OK\n");
   }

   sleep(delay_sec);
   usleep(delay_usec);
   // put original image back
   memcpy(fbp,&(original[0]),screensize);
   close_screen_stream();
   // cleanup

   return 0;

}

/*********************MOTOR*************************/
// sets motor speed and direction
int set_motor(int motor,int speed)
{
    if ((motor>2)||(motor<0))
    {
        printf("Wrong motor number\n");
        return -1;
    }

    if ((speed>255)||(speed<-255))
    {
        printf("Speed should be in range -255..255\n");
        return -3;
    }

    // set PWM for motor1
    if (motor == 1)
    {
        if (speed >= 0)
        {
           gpioPWM(12,speed);
           gpioPWM(16,0);
        } else
        {
           gpioPWM(16,0-speed);
           gpioPWM(12,0);
        }
    }
    // set PWM for motor 2
    if (motor == 2)
    {
        if (speed>=0)
        {
           gpioPWM(20,speed);
           gpioPWM(21,0);
        } else
        {
           gpioPWM(21,0-speed);
           gpioPWM(20,0);
        }
    }
    return 0;
}


/*******************INPUT/output*********************/

int sleep1(int sec, int usec)
{
    int result = gpioSleep(PI_TIME_RELATIVE,sec,usec);
    return result;
}

int select_IO(int chan, int direct)
{
    int d_chan;
    int res =-1;
    if (chan == 0) { d_chan = 4 ;}
    if (chan == 1) { d_chan = 17; }
    if (chan == 2) {d_chan = 27; }
    if (chan == 3) {d_chan = 22; }
    if (chan == 4) {d_chan = 6; }
    if (chan == 5) {d_chan = 13; }
    if (chan == 6) {d_chan = 19; }
    if (chan == 7) {d_chan = 26; }
    if ( direct==0 )
    {
        res = gpioSetMode(d_chan,PI_OUTPUT);
        res = gpioSetPullUpDown(d_chan,PI_PUD_DOWN);
    }
    if (direct == 1 )
    {
        res = gpioSetMode(d_chan,PI_INPUT);
        res = gpioSetPullUpDown(d_chan,PI_PUD_DOWN);
    }
    return res;
}

int write_digital(int chan,char level)
{
    int d_chan;
    if (chan == 0) {d_chan = 4;}
    if (chan == 1) {d_chan = 17;}
    if (chan == 2) {d_chan = 27;}
    if (chan == 3) {d_chan = 22;}
    if (chan == 4) {d_chan = 6;}
    if (chan == 5) {d_chan = 13;}
    if (chan == 6) {d_chan = 19;}
    if (chan == 7) {d_chan = 26;}

    int result = gpioWrite(d_chan,level);
    return result;
}

int read_digital(int chan)
{
    int d_chan;
    if (chan == 0) {d_chan = 4;}
    if (chan == 1) {d_chan = 17;}
    if (chan == 2) {d_chan = 27;}
    if (chan == 3) {d_chan = 22;}
    if (chan == 4) {d_chan = 6;}
    if (chan == 5) {d_chan = 13;}
    if (chan == 6) {d_chan = 19;}
    if (chan == 7) {d_chan = 26;}

    int result = gpioRead(d_chan);
    return result;
}

int set_PWM(int chan, int value)
{
    int d_chan;
    if (chan == 0) {d_chan = 4;}
    if (chan == 1) {d_chan = 17;}
    if (chan == 2) {d_chan = 27;}
    if (chan == 3) {d_chan = 22;}
    if (chan == 4) {d_chan = 6;}
    if (chan == 5) {d_chan = 13;}
    if (chan == 6) {d_chan = 19;}
    if (chan == 7) {d_chan = 26;}
    gpioPWM(d_chan, value);
    return 1;
}

int set_PWM_frequency(int chan, int freq)
{
    int d_chan;
    if (chan == 0) {d_chan = 4;}
    if (chan == 1) {d_chan = 17;}
    if (chan == 2) {d_chan = 27;}
    if (chan == 3) {d_chan = 22;}
    if (chan == 4) {d_chan = 6;}
    if (chan == 5) {d_chan = 13;}
    if (chan == 6) {d_chan = 19;}
    if (chan == 7) {d_chan = 26;}
    gpioSetPWMfrequency(d_chan, freq);
    return 1;
}

int set_servo(int chan, int value)
{
    int d_chan;
    if (chan == 0) {d_chan = 4;}
    if (chan == 1) {d_chan = 17;}
    if (chan == 2) {d_chan = 27;}
    if (chan == 3) {d_chan = 22;}
    if (chan == 4) {d_chan = 6;}
    if (chan == 5) {d_chan = 13;}
    if (chan == 6) {d_chan = 19;}
    if (chan == 7) {d_chan = 26;}
    gpioServo(d_chan, value);
    return 1;
}


  // read analog voltage from ADC
int read_analog(int in_ch_adc)
{
    char txBuf[3],rxBuf[3];
    int ch_adc;

    // PCB was marked wrong way
    if (in_ch_adc == 0 )   { ch_adc = 7; }
    if (in_ch_adc == 1 )   { ch_adc = 6; }
    if (in_ch_adc == 2 )   { ch_adc = 5; }
    if (in_ch_adc == 3 )   { ch_adc = 4; }
    if (in_ch_adc == 4 )   { ch_adc = 3; }
    if (in_ch_adc == 5 )   { ch_adc = 2; }
    if (in_ch_adc == 6 )   { ch_adc = 1; }
    if (in_ch_adc == 7 )   { ch_adc = 0; }


    //printf("   ch_adc=%d\n",ch_adc);
    int ch_adc_b0 = ch_adc&1;
    int ch_adc_b1 = (ch_adc&2)>>1;
    int ch_adc_b2 = (ch_adc&4)>>2;
    if (disp_level>1)
     {
       printf("     b2 = %d b1 = %d b0 =%d\n",ch_adc_b0,ch_adc_b1,ch_adc_b2);
     }
    txBuf[0] = 1;
    txBuf[1] = 8 | (ch_adc_b2<<2) | (ch_adc_b1<<1) | ch_adc_b0 ;
    txBuf[1] = txBuf[1]<<4;
    txBuf[2] = 0;
    //sprintf(txBuf,"\x01\xF0\x00");
    if (disp_level>1)
     {
       printf("     txBuf[0]=%x txBuf[1]=%x txBuf[2]=%x\n",txBuf[0],txBuf[1],txBuf[2]);
     }
    //spiWrite(spi_h,txBuf,3);
    spiXfer(spi_h,txBuf,rxBuf,3);
    //printf("      rxBuf[0]=%x rxBuf[1]=%x rxBuf[2]=%x\n",rxBuf[0],rxBuf[1],rxBuf[2]);

    int adc_value = ((rxBuf[1]&3) << 8) | (rxBuf[2]) ;
    //printf(" in_volt=%d\n",adc_value);
    return adc_value;
}

/*********************************/
/****************NETWORK**********/
/*********************************/

int connect_to_server( char server_addr[15],int port)
{
    int res;
    struct sockaddr_in server;

    if (disp_level>0)
    {
        printf("Connecting to %s \n",server_addr);
    }
    //char server_addr[15] = {'1','2','7','.','0','0','1','.','0','0','1','.','0','0','1'};
    sock = socket(AF_INET,SOCK_STREAM,0);
    if (sock == -1)
    {
        printf("Could not create socket\n");
        res = -1;
        return res;
    }

    server.sin_addr.s_addr = inet_addr(server_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (connect(sock,(struct sockaddr *)&server,sizeof(server))<0)
    {
        printf("Connection to %s failed\n",server_addr);
        return -2;
    }

    if (disp_level>0)
    {
        printf("Connection to %s established\n",server_addr);
    }
    return 0;
}

int send_to_server(char message[24])
{
    if (sock>0)
    {
        if (send(sock , message , strlen(message) , 0) < 0)
        {
            printf("Sending %s failed\n",message);
            return -1;
        }
    } else {
        printf("No connection\n");
    }
    return 0;
}

int receive_from_server(char message[24])
{
    if (sock>0){
        if (recv(sock,message,2000,0) <0) {
            printf("Receive failed\n");
        }
    } else {
        printf("No connection\n");
    }
    return 0;
}

