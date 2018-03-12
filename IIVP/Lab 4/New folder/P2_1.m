clc;
clear;
p=imread('cameraman.tif');
z=double(p);
[row col]=size(z);
for i=1:1:row
for j=1:1:col
if(z(i,j)>50)&&(z(i,j)<150)
z(i,j)=255;
else
z(i,j)=0;
end
end
end

subplot(1,2,1);
imshow(p);

subplot(1,2,2);
imshow(uint8(z));