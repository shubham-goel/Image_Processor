#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<iostream>
#include<stdio.h>
#include<cstdio>
#include<string.h>
#include<math.h>
//#include<fstream>


using namespace std;

/**FUNCTION_DECLARATIONS**/
pixel** enhancecontrast(pixel** image, int height, int width, int boxlength);
pixel** quick_contrast(pixel** image, int height, int width);
pixel** warp_image(pixel**image, int height, int width, double P1_x, double P1_y,double P2_x, double P2_y,double P3_x, double P3_y,double P4_x, double P4_y );
pixel** invert_horizontally(pixel**input_image,int height,int width);
pixel** invert_vertically(pixel**input_image,int height,int width);
pixel** rotate_image(pixel**image,int height, int width, int origin_x, int origin_y, int degree);
pixel** stretch_image(pixel**image, int height, int width, double vertical_coefficient, double horizontal_coefficient);
double minimum(double a, double b);
double maximum(double a, double b);
pixel** new_pixel_array(int height, int width);
hsl_pixel** new_hsl_pixel_array(int height, int width);
int** new_int_array(int height, int width);
void contrast_histogram_cdf(hsl_pixel**image,int top_left_x,int top_left_y, int bottom_right_x,int bottom_right_y,int*histogram);
void delete_image(pixel**image,int height, int width);
void delete_hsl_image(hsl_pixel**image,int height, int width);
void delete_int_array(int**int_array,int height);
void swap_pixels(pixel&a,pixel&b);
FILE* save_img_to_file(pixel**image, int height, int width, FILE*in_image, char filename[]);
pixel** image_pixel_array(char in_filename[]);
unsigned int image_width(char filename[]);
unsigned int image_height(char filename[]);
pixel hsl_to_rgb(hsl_pixel b);
hsl_pixel rgb_to_hsl(pixel rgb);
pixel** crop_image(pixel**image,unsigned int height,unsigned int width, int x1, int y1, int x2, int y2);

/*********FUNCTIONS BY KAUSHIK***********/
/*****************BEGIN******************/


/*****************END******************/



pixel** stretch_image(pixel**image, int height, int width, double vertical_coefficient, double horizontal_coefficient){
    int new_height=height*vertical_coefficient,new_width=width*horizontal_coefficient;
    pixel**new_image=new_pixel_array(new_height,new_width);
    for(int i=0;i<new_height;i++)
    {
        int I=i/vertical_coefficient;
        for(int j=0;j<new_width;j++)
        {
            int J=j/horizontal_coefficient;
            if(I<0){I=0;}
            else if(I>=height){I=height-1;}
            if(J<0){J=0;}
            else if(J>=width){J=width;}
            new_image[i][j]=image[I][J];
        }
    }
    return new_image;

}
pixel** warp_image(pixel**image, int height, int width, double P1_x, double P1_y,double P2_x, double P2_y,double P3_x, double P3_y,double P4_x, double P4_y ){
    pixel**new_image=new_pixel_array(height,width);
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            int I=(P1_x+((P2_x-P1_x)*j)/width+((P4_x-P1_x)*i)/height+((P1_x-P2_x+P3_x-P4_x)*i*j)/(height*width))*height;
            int J=(P1_y+((P2_y-P1_y)*j)/width+((P4_y-P1_y)*i)/height+((P1_y-P2_y+P3_y-P4_y)*i*j)/(height*width))*width;
            if(I<0){I=0;}
            else if(I>=height){I=height-1;}
            if(J<0){J=0;}
            else if(J>=width){J=width;}
            new_image[i][j]=image[I][J];
        }
    }
    delete_image(image,height,width);
    return new_image;
}
pixel** rotate_image(pixel**image,int height, int width, int origin_x, int origin_y, int degree){

    double pi=3.14159265359;
    double theta=(degree*pi)/180;
    theta=-theta;
    double sine_theta=sin(theta),cos_theta=cos(theta);

    int new_height=maximum(fabs(height*cos_theta+width*sine_theta),fabs(height*cos_theta-width*sine_theta));
    int new_width=maximum(fabs(width*cos_theta+height*sine_theta),fabs(width*cos_theta-height*sine_theta));

    pixel**new_image=new_pixel_array(new_height,new_width);
    if(new_pixel_array==NULL){return NULL;}

    /**modification**/
    origin_x=new_height/2;
    origin_y=new_width/2;

    for(int i=0;i<new_height;i++)
    {
        for(int j=0;j<new_width;j++)
        {
            int J=(i*1.0-origin_x)*sine_theta+(j*1.0-origin_y)*cos_theta+width/2.0;
            int I=(i*1.0-origin_x)*cos_theta-(j*1.0-origin_y)*sine_theta+height/2.0;
            if(I<0||J<0||I>=height||J>=width){new_image[i][j]={255,255,255};}
            else{new_image[i][j]=image[I][J];}
        }
    }
    delete_image(image,height,width);
    return new_image;
}

pixel** enhancecontrast(pixel** image, const int height, const int width, int boxlength){

    pixel** new_image=new_pixel_array(height,width);
    if(new_image==NULL){return NULL;}

    int top_left_x,top_left_y,bottom_right_x,bottom_right_y;

    boxlength=minimum(height,minimum(width,boxlength));
    if(boxlength%2==0){boxlength--;}
    if(boxlength==0){return NULL;}

    int*histogram_cdf=new int[501];
    if(histogram_cdf==NULL){return NULL;}

    hsl_pixel**hsl_image=new_hsl_pixel_array(height,width);
    if(hsl_image==NULL){return NULL;}
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            hsl_image[i][j]=rgb_to_hsl(image[i][j]);
        }
    }

    hsl_pixel**new_hsl_image=new_hsl_pixel_array(height,width);

    for(int i=0;i<height;i++)
    {
        if(i<=boxlength/2){top_left_x=0;bottom_right_x=boxlength-1;}
        else if(i>=height-boxlength/2-1){top_left_x=height-boxlength;bottom_right_x=height-1;}
        else{top_left_x=i-boxlength/2;bottom_right_x=i+boxlength/2;}

//        printf("Progress: %5.2f%\n",i*1.0/height*100);
        for(int j=0;j<width;j++)
        {
            if(j<=boxlength/2){top_left_y=0;bottom_right_y=boxlength-1;}
            else if(j>=width-boxlength/2-1){top_left_y=width-boxlength;bottom_right_y=width-1;}
            else{top_left_y=j-boxlength/2;bottom_right_y=j+boxlength/2;}
            contrast_histogram_cdf(hsl_image,top_left_x,top_left_y,bottom_right_x,bottom_right_y,histogram_cdf);
            new_hsl_image[i][j]=hsl_image[i][j];
            new_hsl_image[i][j].lightness=((histogram_cdf[(hsl_image[i][j].lightness)/20])*10000.0)/(boxlength*boxlength);
            if(new_hsl_image[i][j].lightness>=10000){new_hsl_image[i][j].lightness=9999;}
            if(new_hsl_image[i][j].lightness<0){new_hsl_image[i][j].lightness=0;}

        }
    }

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            new_image[i][j]=hsl_to_rgb(new_hsl_image[i][j]);
        }
    }


    delete_image(image, height, width);
    delete_hsl_image(hsl_image,height,width);
    delete_hsl_image(new_hsl_image,height,width);
    delete[] histogram_cdf;
    return new_image;

};

pixel** quick_contrast(pixel** image, const int height, const int width){

    pixel** new_image=new_pixel_array(height,width);
    if(new_image==NULL){return NULL;}

    int*histogram_cdf=new int[501];
    if(histogram_cdf==NULL){return NULL;}

    hsl_pixel**hsl_image=new_hsl_pixel_array(height,width);
    if(hsl_image==NULL){return NULL;}
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            hsl_image[i][j]=rgb_to_hsl(image[i][j]);
        }
    }

    hsl_pixel**new_hsl_image=new_hsl_pixel_array(height,width);

    contrast_histogram_cdf(hsl_image,0,0,height-1,width-1,histogram_cdf);

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            new_hsl_image[i][j]=hsl_image[i][j];
            new_hsl_image[i][j].lightness=((histogram_cdf[(hsl_image[i][j].lightness)/20])*10000.0)/(height*width);
            if(new_hsl_image[i][j].lightness>=10000){new_hsl_image[i][j].lightness=9999;}
            if(new_hsl_image[i][j].lightness<0){new_hsl_image[i][j].lightness=0;}

        }
    }

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            new_image[i][j]=hsl_to_rgb(new_hsl_image[i][j]);
        }
    }


    delete_image(image, height, width);
    delete_hsl_image(hsl_image,height,width);
    delete_hsl_image(new_hsl_image,height,width);
    delete[] histogram_cdf;
    return new_image;

};

void contrast_histogram_cdf(hsl_pixel**image,int top_left_x,int top_left_y, int bottom_right_x,int bottom_right_y,int*histogram){

    for(int i=0;i<501;i++)
    {
        histogram[i]=0;
    }
    for(int i=top_left_x;i<=bottom_right_x;i++)
    {

        for(int j=top_left_y;j<=bottom_right_y;j++)
        {
            histogram[image[i][j].lightness/20]++;
        }
    }
    for(int i=1;i<501;i++)
    {
        histogram[i]+=histogram[i-1];
    }
    return;
}
pixel** invert_horizontally(pixel**input_image,int height,int width){

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width/2;j++)
        {
            swap_pixels(input_image[i][j],input_image[i][width-j-1]);
        }
    }
    return input_image;
}
pixel** invert_vertically(pixel**input_image,int height,int width){
    for(int i=0;i<height/2;i++)
    {
        for(int j=0;j<width;j++)
        {
            swap_pixels(input_image[i][j],input_image[height-i-1][j]);
        }
    }
    return input_image;
}

pixel** image_pixel_array(char in_filename[]){

    FILE*in_image=fopen(in_filename,"rb+");
    unsigned int height,width;
    if(in_image==NULL){return NULL;}
    fseek(in_image,18,SEEK_SET);
    fread(&width,4,1,in_image);

    fseek(in_image,22,SEEK_SET);

    fread(&height,4,1,in_image);

    fseek(in_image,54,SEEK_SET);
    pixel**image=new_pixel_array(height,width);
    if(image==NULL){return NULL;}
    int padded_width=3-(width*3+3)%4;
    for(int i=height-1;i>=0;i--)
    {
        for(int j=0;j<width;j++)
        {
            fread(&image[i][j].blue,1,1,in_image);
            fread(&image[i][j].green,1,1,in_image);
            fread(&image[i][j].red,1,1,in_image);
        }
        fseek(in_image,padded_width,SEEK_CUR);
    }
    return image;


}
unsigned int image_height(char filename[]){
    FILE*img_file=fopen(filename,"rb+");
    if(img_file==NULL){return 0;}
    fseek(img_file,22,SEEK_SET);
    unsigned int height;
    fread(&height,4,1,img_file);
    fclose(img_file);
    return height;
}
unsigned int image_width(char filename[]){
    FILE*img_file=fopen(filename,"rb+");
    if(img_file==NULL){return 0;}
    fseek(img_file,18,SEEK_SET);
    unsigned int width;
    fread(&width,4,1,img_file);
    fclose(img_file);
    return width;
}
FILE* save_img_to_file(pixel**image, int height, int width, FILE*in_image, char filename[]){
    FILE*out_image=fopen(filename,"wb+");
    if(out_image==NULL){return NULL;}
    char header[20];
    if(in_image==NULL){return NULL;}
    fseek(in_image,0,SEEK_SET);
    fseek(out_image,0,SEEK_SET);
    for(int i=0;i<2;i++)
    {
        fread(header,1,1,in_image);
        fwrite(header,1,1,out_image);
    }
    int in_size,in_width,in_height,in_padded_width,out_padding,out_padded_width,out_size;
    out_padding=3-(width*3+3)%4;
    out_padded_width=out_padding+width;

    fread(&in_size,4,1,in_image);
    fseek(in_image,18,SEEK_SET);
    fread(&in_width,4,1,in_image);
    fread(&in_height,4,1,in_image);

    in_padded_width=(in_width*3+3)-(in_width*3+3)%4;
    out_size=in_size+(height*3*out_padded_width)-(in_height*3*in_padded_width);

    fseek(out_image,2,SEEK_SET);
    fwrite(&out_size,4,1,out_image);
    fseek(in_image,6,SEEK_SET);
    for(int i=0;i<12;i++)
    {
        fread(header,1,1,in_image);
        fwrite(header,1,1,out_image);
    }

    fseek(out_image,18,SEEK_SET);
    fwrite(&width,4,1,out_image);
    fseek(out_image,22,SEEK_SET);
    fwrite(&height,4,1,out_image);
    fseek(out_image,26,SEEK_SET);
    fseek(in_image,26,SEEK_SET);
    for(int i=0;i<28;i++)
    {
        fread(header,1,1,in_image);
        fwrite(header,1,1,out_image);
    }

    for(int i=height-1;i>=0;i--)
    {
        for(int j=0;j<width;j++)
        {
            fwrite(&image[i][j].blue,1,1,out_image);
            fwrite(&image[i][j].green,1,1,out_image);
            fwrite(&image[i][j].red,1,1,out_image);
        }
        fseek(out_image,out_padding,SEEK_CUR);
    }
    fseek(in_image,3*in_height*in_padded_width,SEEK_CUR);

    char temporary_value;
    while(!feof(in_image))
    {
        fread(&temporary_value,1,1,in_image);
        fwrite(&temporary_value,1,1,out_image);

    }

    return out_image;
}
void swap_pixels(pixel&a,pixel&b){
    pixel temp=a;
    a=b;
    b=temp;
    return;
}
void delete_image(pixel**image,int height, int width){
    if(image==NULL){return;}
    for(int i=0;i<height;i++)
    {
        if(image[i]!=NULL){delete[] image[i];}
    }
    delete[] image;
    return;
}
void delete_hsl_image(hsl_pixel**image,int height, int width){

    for(int i=0;i<height;i++)
    {
        delete[] image[i];
    }
    delete[] image;
    return;
}

void delete_int_array(int**int_array,int height){

    for(int i=0;i<height;i++)
    {
        delete[] int_array[i];
    }
    delete[] int_array;
    return;
}
pixel** new_pixel_array(int height, int width){
    pixel**pixel_array=new pixel*[height];
    if(pixel_array==NULL){return NULL;}
    for(int i=0;i<height; i++)
    {
        pixel_array[i]=new pixel[width];
        if(pixel_array[i]==NULL){return NULL;}
    }
    return pixel_array;
}
hsl_pixel** new_hsl_pixel_array(int height, int width){
    hsl_pixel**pixel_array=new hsl_pixel*[height];
    if(pixel_array==NULL){return NULL;}
    for(int i=0;i<height; i++)
    {
        pixel_array[i]=new hsl_pixel[width];
        if(pixel_array[i]==NULL){return NULL;}
    }
    return pixel_array;
}
int** new_int_array(int height, int width){
    int**int_array=new int*[height];
    if(int_array==NULL){return NULL;}
    for(int i=0;i<height;i++)
    {
        int_array[i]=new int[width];
        if(int_array==NULL){return NULL;}
        for(int j=0;j<width;j++)
        {
            int_array[i][j]=0;
        }
    }
    return int_array;
}
double minimum(double a, double b){
    if(a<b){return a;}
    else return b;
}
double maximum(double a, double b){
    if(a>b){return a;}
    else return b;
}
pixel hsl_to_rgb(hsl_pixel b){
    pixel a;
    double h=b.hue/36000.0;
    double s=b.saturation/10000.0;
    double l=b.lightness/10000.0;
    if(s==0){a.red=a.green=a.blue=l*255; return a;}
    double temp_1;
    if(l>=0.5){temp_1=l+s-l*s;}
    else{temp_1=l*(1+s);}
    double temp_2=2*l-temp_1;
    double temp_r=h+0.333333;
    double temp_g=h;
    double temp_b=h-0.333333;
    if(temp_r>1){temp_r-=1;}
    if(temp_b<0){temp_b+=1;}
    if(6*temp_r<1){a.red=(temp_2+(temp_1-temp_2)*6*temp_r)*255+0.5;}
    else if(2*temp_r<1){a.red=temp_1*255+0.5;}
    else if(3*temp_r<2){a.red=(temp_2+(temp_1-temp_2)*(0.666666-temp_r)*6)*255+0.5;}
    else {a.red=temp_2*255+0.5;}

    if(6*temp_g<1){a.green=(temp_2+(temp_1-temp_2)*6*temp_g)*255+0.5;}
    else if(2*temp_g<1){a.green=temp_1*255+0.5;}
    else if(3*temp_g<2){a.green=(temp_2+(temp_1-temp_2)*(0.666666-temp_g)*6)*255+0.5;}
    else {a.green=temp_2*255+0.5;}

    if(6*temp_b<1){a.blue=(temp_2+(temp_1-temp_2)*6*temp_b)*255+0.5;}
    else if(2*temp_b<1){a.blue=temp_1*255+0.5;}
    else if(3*temp_b<2){a.blue=(temp_2+(temp_1-temp_2)*(0.666666-temp_b)*6)*255+0.5;}
    else {a.blue=temp_2*255+0.5;}

    return a;
}
hsl_pixel rgb_to_hsl(pixel rgb){

    hsl_pixel a;
    double r=rgb.red/255.0;
    double g=rgb.green/255.0;
    double b=rgb.blue/255.0;
    double mini=minimum(r,minimum(g,b));
    double maxi=maximum(r,maximum(g,b));
    double l=(mini+maxi)/2;
    if(mini==maxi){a.lightness=l*10000;a.hue=0;a.saturation=0;return a;}
    double s;
    if(l<=0.5){s=(maxi-mini)/(maxi+mini);}
    else {s=(maxi-mini)/(2-maxi-mini);}
    double h;
    if(r==maxi){h=(g-b)/(maxi-mini);}
    else if(g==maxi){h=2.0+(b-r)/(maxi-mini);}
    else {h=4.0+(r-g)/(maxi-mini);}

    h*=60;
    if(h<0){h+=360;}
    a.hue=h*100+.05;
    a.saturation=s*10000.0+0.5;
    a.lightness=l*10000.0+0.5;
    return a;

}

pixel** crop_image(pixel**image,unsigned int height,unsigned int width, int x1, int y1, int x2, int y2){
    int new_height=x2-x1;
    int new_width=y2-y1;
    if(new_height<=0||new_width<=0){return NULL;}
    if(x1<0||y1<0||x2>height||y2>width){return NULL;}
    pixel**new_image=new_pixel_array(new_height,new_width);
    if(new_image==NULL){return NULL;}
    for(int i=0;i<new_height;i++){
        for(int j=0;j<new_width;j++){
            new_image[i][j]=image[i+x1][j+y1];
        }
    }
    delete_image(image,height,width);
    return new_image;
}


double**new_double_array(int height,int width){
    double**new_array=new double*[height];
    if(new_array==NULL){return NULL;}
    for(int i=0;i<height;i++){
        new_array[i]=new double [width];
        if(new_array[i]==NULL){return NULL;}
    }
    return new_array;
}

pixel**box_blur(pixel**image,int height,int width,int iterations){

    pixel**image2=new_pixel_array(height,width);
    if(image2==NULL){return NULL;}

    if(height<=2||width<=2){return image;}
    for(int k=0;k<iterations;k++){
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                double sum1=0,sum2=0,sum3=0;
                int sum_count=0;
                for(int m=i-1;m<i+2;m++){
                    for(int n=j-1;n<j+2;n++){
                        if(m>=0&&m<height&&n>=0&&n<width){
                            sum1+=(int)image[m][n].red;
                            sum2+=(int)image[m][n].green;
                            sum3+=(int)image[m][n].blue;
                            sum_count++;

                        }
                    }
                }
                sum1/=sum_count;
                sum2/=sum_count;
                sum3/=sum_count;
                image2[i][j].red=(int)sum1;
                image2[i][j].green=(int)sum2;
                image2[i][j].blue=(int)sum3;
            }
        }
        pixel**temp=image2;
        image2=image;
        image=temp;
    }
    delete_image(image,height,width);
    return image2;
}

pixel**change_brightness(pixel**image,int height,int width,float factor){
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            hsl_pixel temp=rgb_to_hsl(image[i][j]);

        }
    }
    return image;
}

/*********FUNCTIONS BY KAUSHIK***********/
/*****************BEGIN******************/

//COLOR TO GRAYSCALE:
pixel** colortogray(pixel** img,int rows,int columns)
{
int i,j;
i=j=0;
pixel** img1=new_pixel_array(rows,columns);
if(img1==NULL){
    return NULL;
}

for(i=0;i<rows;i++)
{
for(j=0;j<columns;j++)
{
float x=0.2125*img[i][j].red+0.7154*img[i][j].green+0.0721*img[i][j].blue;
img1[i][j].red=img1[i][j].blue=img1[i][j].green=(int)x;
}
}

delete_image(img,rows,columns);
return img1;
}

pixel** half_tone(pixel** img,int rows,int columns)
{
    int i,j,m,n,x,y;
    float sum,t;
    int threshold=95;
    i=j=0;
    pixel** img1=new pixel*[rows];
    if(img1==NULL)
    return NULL;
    for(i=0;i<rows;i++)
    {
        img1[i]=new pixel[columns];
    }
    float** ep=new float*[rows];
    for(i=0;i<rows;i++)
    {
        ep[i]=new float[columns];
    }
    float** eg=new float*[rows];
    for(i=0;i<rows;i++)
    {
        eg[i]=new float[columns];
    }
    for(i=0;i<rows;i++)
    {
        for(j=0;j<columns;j++)
        {
            float x=0.2125*img[i][j].red+0.7154*img[i][j].green+0.0721*img[i][j].blue;
            img1[i][j].red=img1[i][j].blue=img1[i][j].green=(int)x;
        }
    }

    float c[2][3];
    c[0][0]=0.0;
    c[0][1]=0.2;
    c[0][2]=0.0;
    c[1][0]=0.6;
    c[1][1]=0.1;
    c[1][2]=0.1;

    for(i=0;i<rows;i++)
    {
        for(j=0;j<columns;j++)
        {
            ep[i][j]=0;
            eg[i][j]=0;
        }
    }
    for(i=0;i<rows;i++)
    {
        for(j=0;j<columns;j++)
        {
            sum=0;
            for(m=0;m<2;m++)
            {
                for(n=0;n<3;n++)
                {
                    x=i+1-m;
                    y=j+1-n;
                    if(x<0)
                    x=0;
                    if(y<0)
                    y=0;
                    if(x>=rows)
                    x=rows-1;
                    if(y>=columns)
                    y=columns-1;
                    sum=sum+c[m][n]*eg[x][y];
                }
            }
            ep[i][j]=sum;
            t=img1[i][j].red+ep[i][j];
            if(t>threshold)
            {
                eg[i][j]=t-256;
                img[i][j].red=img[i][j].blue=img[i][j].green=255;
            }
            else
            {
                eg[i][j]=t;
                img[i][j].red=img[i][j].blue=img[i][j].green=0;
            }
        }
    }

    for(i=0;i<rows;i++)
    {
        delete[] img1[i];
    }
    delete[] img1;
    return img;
}



pixel** blur(pixel** img,int rows,int columns,int rad)
{
int i,j;
pixel** img1=new_pixel_array(rows,columns);
if(img1==NULL)
return NULL;



double** t1=new double*[2*rad+1];
if(t1==NULL)
return NULL;
for(i=0;i<2*rad+1;i++)
{
t1[i]=new double[2*rad+1];
}
double** t2=new double*[2*rad+1];
if(t2==NULL)
return NULL;
for(i=0;i<2*rad+1;i++)
{
t2[i]=new double[2*rad+1];
}
double** t3=new double*[2*rad+1];
if(t3==NULL)
return NULL;
for(i=0;i<2*rad+1;i++)
{
t3[i]=new double[2*rad+1];
}
double sum1=0,sum2=0;
for(i=-1*rad;i<=rad;i++)
{
for(j=-1*rad;j<=rad;j++)
{
sum1=sum1+sqrt(i*i+j*j);
sum2=sum2+i*i+j*j;
}
}
double mean1=sum1/pow(2*rad+1,2);
double mean2=sum2/pow(2*rad+1,2);
double sigma1=sqrt(mean2-pow(mean1,2));
struct coordinate
{
int x,y;
double w;
void calc(double sigma)
{
w=exp(-1*(x*x+y*y)/(2*sigma*sigma))/(2*3.14*sigma*sigma);
}
};
coordinate** c=new coordinate*[2*rad+1];
if(c==NULL)
return NULL;
for(i=0;i<2*rad+1;i++)
{
c[i]=new coordinate[2*rad+1];
}
for(i=0;i<2*rad+1;i++)
{
for(j=0;j<2*rad+1;j++)
{
c[i][j].x=j-rad;
c[i][j].y=rad-i;
c[i][j].calc(sigma1);
}
}
double sum=0;
for(i=0;i<2*rad+1;i++)
{
for(j=0;j<2*rad+1;j++)
{
sum=sum+c[i][j].w;
}
}
for(i=0;i<2*rad+1;i++)
{
for(j=0;j<2*rad+1;j++)
{
c[i][j].w=c[i][j].w/sum;
}
}
int m,n,p,q;
double sumr,sumg,sumb;
double weight_sum;
for(i=0;i<rows;i++)
{
for(j=0;j<columns;j++)
{
sumr=sumg=sumb=0;
weight_sum=0;
for(m=i-rad,p=0;m<=i+rad;m++,p++)
{
for(n=j-rad,q=0;n<=j+rad;n++,q++)
{
if(m>=0&&m<rows&&n>=0&&n<columns){
    t1[p][q]=img[m][n].red*c[p][q].w;
    t2[p][q]=img[m][n].green*c[p][q].w;
    t3[p][q]=img[m][n].blue*c[p][q].w;
    weight_sum+=c[p][q].w;
    sumr=sumr+t1[p][q];
    sumg=sumg+t2[p][q];
    sumb=sumb+t3[p][q];
}
}
}
img1[i][j].red=sumr/weight_sum;
img1[i][j].green=sumg/weight_sum;
img1[i][j].blue=sumb/weight_sum;
}
}
for(i=0;i<rows;i++)
{
delete[] img[i];
}
delete[] img;

return img1;
}


pixel** edge_detect(pixel** img,int rows,int columns)
{
    pixel** img1=new_pixel_array(rows,columns);
    if(img1==NULL){return NULL;}

    int i,j,m,n;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<columns;j++)
        {
            img1[i][j].red=img1[i][j].green=img1[i][j].blue=0.2125*img[i][j].red+0.7154*img[i][j].green+0.0721*img[i][j].blue;;
        }
    }

    int gx[3][3]={{-1,0,1},{-2,0,2},{-1,0,1}};
    int gy[3][3]={{1,2,1},{0,0,0},{-1,-2,-1}};
    int sumx=0,sumy=0,sum=0;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<columns;j++)
        {
            sumx=0;
            sumy=0;
            if(i==0||i==rows-1)
            sum=0;
            else if(j==0||j==columns-1)
            sum=0;
            else
            {
                for(m=-1;m<=1;m++)
                {
                    for(n=-1;n<=1;n++)
                    {
                        int x=i+m;
                        int y=j+n;

                        sumx=sumx+gx[n+1][m+1]*img1[x][y].red;
                        sumy=sumy+gy[n+1][m+1]*img1[x][y].red;
                    }
                }
                sum=fabs(sumx)+fabs(sumy);
            }
            if(sum>255)
            sum=255;
            if(sum<0)
            sum=0;
            img[i][j].red=img[i][j].green=img[i][j].blue=sum;
        }
    }

        for(i=0;i<rows;i++)
        {
            delete[] img1[i];
        }
        delete img1;
        return img;

}

//DITHER:

pixel** dither(pixel** img,int rows,int columns)
{
int i,j,error1,error2,error3,t1,t2,t3;
int threshold=150;
for(i=0;i<rows;i++)
{
for(j=0;j<columns;j++)
{
t1=img[i][j].red;
t2=img[i][j].green;
t3=img[i][j].blue;
if(img[i][j].red>threshold)
{
img[i][j].red=255;
error1=t1-255;
}
else
{
img[i][j].red=0;
error1=t1;
}
if(img[i][j].green>threshold)
{
img[i][j].green=255;
error2=t2-255;
}
else
{
img[i][j].green=0;
error2=t2;
}
if(img[i][j].blue>threshold)
{
img[i][j].blue=255;
error3=t3-255;
}
else
{
img[i][j].blue=0;
error3=t3;
}
if(i<rows-1)
{
img[i+1][j].red+=error1*7/16;
img[i+1][j].green+=error2*7/16;
img[i+1][j].blue+=error3*7/16;
}
if(i>0&&j<columns-1)
{
img[i-1][j+1].red+=error1*3/16;
img[i-1][j+1].green+=error2*3/16;
img[i-1][j+1].blue+=error3*3/16;
}
if(j<columns-1)
{
img[i][j+1].red+=error1*5/16;
img[i][j+1].green+=error2*5/16;
img[i][j+1].blue+=error3*5/16;
}
if(i<rows-1&&j<columns-1)
{
img[i+1][j+1].red+=error1*1/16;
img[i+1][j+1].green+=error2*1/16;
img[i+1][j+1].blue+=error3*1/16;
}
}
}
return img;
}

//SEPIA:

pixel** sepia(pixel** img,int rows,int columns)
{
int** gr=new int*[rows];
if(gr==NULL)
return NULL;
int i,j;
for(i=0;i<rows;i++)
{
gr[i]=new int[columns];
if(gr[i]==NULL)
return NULL;
}
for(i=0;i<rows;i++)
{
for(j=0;j<columns;j++)
{
gr[i][j]=0.3*img[i][j].red+0.59*img[i][j].green+0.11*img[i][j].blue;
}
}
for(i=0;i<rows;i++)
{
for(j=0;j<columns;j++)
{
img[i][j].red=gr[i][j];
img[i][j].green=0.71*gr[i][j];
img[i][j].blue=0.41*gr[i][j];
}
}
for(i=0;i<rows;i++)
{
delete[] gr[i];
}
delete[] gr;
return img;
}

//NEGATIVE:

pixel** negative(pixel** img,int rows,int columns)
{
int i,j;
img=colortogray(img,rows,columns);
for(i=0;i<rows;i++)
{
for(j=0;j<columns;j++)
{
img[i][j].red=255-img[i][j].red;
img[i][j].green=255-img[i][j].green;
img[i][j].blue=255-img[i][j].blue;
}
}
return img;
}

//SALT AND PEPPER:

pixel** salt_pepper(pixel** img,int rows,int columns)
{
int i,j,k;
int iter=10*sqrt(rows*columns);
for(k=0;k<iter;k++)
{
i=rand()%rows;
j=rand()%columns;
img[i][j].red=img[i][j].green=img[i][j].blue=0;
}
for(k=0;k<iter;k++)
{
i=rand()%rows;
j=rand()%columns;
img[i][j].red=img[i][j].green=img[i][j].blue=255;
}
return img;
}

pixel** add_hue_blue(pixel** img,int rows,int columns,int hue_val)
{
int i,j;

int temp;
for(i=0;i<rows;i++)
{
for(j=0;j<columns;j++)
{

hsl_pixel temp_hsl=rgb_to_hsl(img[i][j]);
temp_hsl.hue=hue_val;
img[i][j]=hsl_to_rgb(temp_hsl);
}
}
return img;
}

//WATERMARK FOR GRAYSCALE IMAGES:

pixel** watermark(pixel** img,pixel** waterimg,int rows,int columns,int wrows,int wcolumns)
{
int i,j;
//include scaling here *****begin*******
double scale_factor;
    if(wrows>rows){
        if(wcolumns>columns)
            {scale_factor=minimum(rows*1.0/wrows,columns*1.0/wcolumns);}
        else {scale_factor=rows*1.0/wrows;}
    }
    else if(wcolumns>columns)
            {scale_factor=columns*1.0/wcolumns;}
        else {scale_factor=1;}


    pixel**temp=stretch_image(waterimg,wrows,wcolumns,scale_factor,scale_factor);
    delete_image(waterimg,wrows,wcolumns);
    waterimg=temp;
    if(waterimg==NULL){return NULL;}

    wrows=wrows*scale_factor;
    wcolumns=wcolumns*scale_factor;
//*******end********* I hope u understand what I have done!
waterimg=edge_detect(waterimg,wrows,wcolumns);
if(waterimg==NULL){return NULL;}
waterimg=half_tone(waterimg,wrows,wcolumns);
if(waterimg==NULL){return NULL;}


int l=0,m=0;

for(i=(rows-wrows)/2;i<(rows+wrows)/2;i++)
{
if(l>=wrows){;break;}
m=0;
for(j=(columns-wcolumns)/2;j<(columns+wcolumns)/2;j++)
{
if(m>=wcolumns){break;}
if(waterimg[l][m].red==255)
{


img[i][j].red=minimum(img[i][j].red+8,255);
img[i][j].green=minimum(img[i][j].green+8,255);
img[i][j].blue=minimum(img[i][j].blue+8,255);
}
m++;
}
l++;
}
delete_image(waterimg,wrows,wcolumns);
return img;
}


/*****************END******************/

#endif // MYWINDOW_H
