I = imread('pout.tif');
I2 = double(I);
m = mean(I(:));
display(m);
v = var(I2(:));
display(v);
[roww,coll] = size(I);

I2 = I;
for ii = 1:1:roww-3
    for jj = 1:1:coll-3
        GIm=I(ii:ii+3,jj:jj+3);
        numofpixels=size(GIm,1)*size(GIm,2);
        HIm=uint8(zeros(size(GIm,1),size(GIm,2)));
        freq=zeros(256,1);
        probf=zeros(256,1);
        probc=zeros(256,1);
        cum=zeros(256,1);
        output=zeros(256,1);
        for i=1:size(GIm,1)
            for j=1:size(GIm,2)
                value=GIm(i,j);
                freq(value+1)=freq(value+1)+1;
                probf(value+1)=freq(value+1)/numofpixels;
            end
        end

        sum=0;
        no_bins=255;
        for i=1:size(probf)
            sum=sum+freq(i);
            cum(i)=sum;
            probc(i)=cum(i)/numofpixels;
            output(i)=round(probc(i)*no_bins);
        end

    
        for i=1:size(GIm,1)
            for j=1:size(GIm,2)
                HIm(i,j)=output(GIm(i,j)+1);
            end
        end
        I2(ii:ii+3,jj:jj+3) = HIm;
    end
end
I3 = I;
for ii = 1:4:roww-3
    for jj = 1:4:coll-3
        GIm=I(ii:ii+3,jj:jj+3);
        numofpixels=size(GIm,1)*size(GIm,2);
        HIm=uint8(zeros(size(GIm,1),size(GIm,2)));
        freq=zeros(256,1);
        probf=zeros(256,1);
        probc=zeros(256,1);
        cum=zeros(256,1);
        output=zeros(256,1);
        for i=1:size(GIm,1)
            for j=1:size(GIm,2)
                value=GIm(i,j);
                freq(value+1)=freq(value+1)+1;
                probf(value+1)=freq(value+1)/numofpixels;
            end
        end

        sum=0;
        no_bins=255;
        for i=1:size(probf)
            sum=sum+freq(i);
            cum(i)=sum;
            probc(i)=cum(i)/numofpixels;
            output(i)=round(probc(i)*no_bins);
        end

    
        for i=1:size(GIm,1)
            for j=1:size(GIm,2)
                HIm(i,j)=output(GIm(i,j)+1);
            end
        end
        I3(ii:ii+3,jj:jj+3) = HIm;
    end
end
subplot(1,3,1),imshow(I);
subplot(1,3,2),imshow(I2);
subplot(1,3,3),imshow(I3);
