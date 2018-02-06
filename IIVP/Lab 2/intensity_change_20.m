function y = intensity_change_20(x)
    if (x > 250)
        y = 250;
    elseif (x > 230)
        y = 230;
    elseif (x > 210)
        y = 210;
    elseif (x > 190)
        y = 190;
    elseif (x > 170)
        y = 170;    
    elseif (x > 150)
        y = 150;    
    elseif (x > 130)
        y = 130;
    elseif (x > 110)
        y = 110;
    elseif (x > 90)
        y = 90;
    elseif (x > 70)
        y = 70;    
    elseif (x > 50)
        y = 50;
    elseif (x > 30)
        y = 30;
    elseif (x > 10)
        y = 10;
    else
        y = 0;
    end
end