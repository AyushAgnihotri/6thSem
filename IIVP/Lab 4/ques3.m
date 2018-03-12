I = imread('cameraman.tif');
[r,c] = size(I);
c1 = I;
c2 = I;
c3 = I;
c4 = I;
c5 = I;
c6 = I;
c7 = I;
c8 = I;

for i = 1:1:r
    for j = 1:1:c
        if bitand(I(i,j),1) ~= 0
            c1(i,j) = 0;
        else
            c1(i,j) = 255;
        end
        if bitand(I(i,j),2) ~= 0
            c2(i,j) = 0;
        else
            c2(i,j) = 255;
        end    
        if bitand(I(i,j),4) ~= 0
            c3(i,j) = 0;
        else
            c3(i,j) = 255;
        end 
        if bitand(I(i,j),8) ~= 0
            c4(i,j) = 0;
        else
            c4(i,j) = 255;
        end
        if bitand(I(i,j),16) ~= 0
            c5(i,j) = 0;
        else
            c5(i,j) = 255;
        end   
        if bitand(I(i,j),32) ~= 0
            c6(i,j) = 0;
        else
            c6(i,j) = 255;
        end
        if bitand(I(i,j),64) ~= 0
            c7(i,j) = 0;
        else
            c7(i,j) = 255;
        end     
        if bitand(I(i,j),128) ~= 0
            c8(i,j) = 0;
        else
            c8(i,j) = 255;
        end
    end
end

subplot(2,5,1),imshow(I);
subplot(2,5,2),imshow(c1);
subplot(2,5,3),imshow(c2);
subplot(2,5,4),imshow(c3);
subplot(2,5,5),imshow(c4);
subplot(2,5,6),imshow(c5);
subplot(2,5,7),imshow(c6);
subplot(2,5,8),imshow(c7);
subplot(2,5,9),imshow(c8);

I2 = I;
for i=1:1:r
    for j=1:1:c
        I2(i,j) = 0;
        if c1(i,j) == 0
            I2(i,j) = bitor(I2(i,j),1);
        end
        if c2(i,j) == 0
            I2(i,j) = bitor(I2(i,j),2);
        end
        if c3(i,j) == 0
            I2(i,j) = bitor(I2(i,j),4);
        end
        if c4(i,j) == 0
            I2(i,j) = bitor(I2(i,j),8);
        end
        if c5(i,j) == 0
            I2(i,j) = bitor(I2(i,j),16);
        end
        if c6(i,j) == 0
            I2(i,j) = bitor(I2(i,j),32);
        end
        if c7(i,j) == 0
            I2(i,j) = bitor(I2(i,j),64);
        end
        if c8(i,j) == 0
            I2(i,j) = bitor(I2(i,j),128);
        end
    end
end
subplot(2,5,10),imshow(I2);