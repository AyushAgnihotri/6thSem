clear
clc
I=imread('cameraman.tif');
figure,imshow(I)
p=I;
rtemp = min(I);
rmin = min(rtemp); 
rtemp = max(I);        
rmax = max(rtemp);      
disp(rmin);
disp(rmax);

x=0:255;

x1=rmin;
x2=rmax;
y1=0;
y2=0;
 
x_r1 = 0:x1;
x_r2 = x1+1:x2;
x_r3 = x2+1:255;
 
a1 = y1/x1;
a2 = (y2-y1)/(x2-x1);
a3 = (255-y2)/(255-x2);
 
yo_1 = a1*x_r1;
yo_2 = y1 + (a2*(x_r2-x1));
yo_3 = y2 + (a3*(x_r3-x2));
 
y = [yo_1 yo_2 yo_3];
 
plot(x,y),grid on;
xlim([0 255]);
ylim([0 255]);

% Implementing contrast stretching using piece wise linear transform.
[rowi coli]=size(p);
out=zeros(rowi,coli);

for k=1:256
    for i=1:rowi
        for j=1:coli
            if p(i,j)==x(k) 
                out(i,j)=y(k);
end
        end
    end
end
figure,imshow(uint8(out))
figure,imshow(p)