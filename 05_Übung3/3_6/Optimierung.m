%Hi = [1 b1 b2 1 a1 a2] -  die von Matlab vorgegebene Form
H1 = [1 0 -1 1 -1.847929303926 0.9850722601925 ];
H2 = [1 0 -1 1 -1.81768444585  0.9836465239584 ];
H3 = [1 0 -1 1 -1.819862361978 0.9633409060843 ];
H4 = [1 0 -1 1 -1.806715933748 0.9619429222893 ];

%Berechnung der Teilverstärkungen
H=abs(freqz(H1(1:3),H1(4:6)));
g1=1/max(H);
H=g1*H;
H=H.*abs(freqz(H2(1:3),H2(4:6)));
g2=1/max(H);
H=g2*H;
H=H.*abs(freqz(H3(1:3),H3(4:6)));
g3=1/max(H);
H=g3*H;
H=H.*abs(freqz(H4(1:3),H4(4:6)));
g4=1/max(H);

%Die von unserem Filter benötigte Form
H1 = [-1 0 1 -0.9850722601925 1.847929303926]/2;
H2 = [-1 0 1 -0.9836465239584 1.81768444585 ]/2;
H3 = [-1 0 1 -0.9633409060843 1.819862361978]/2;
H4 = [-1 0 1 -0.9619429222893 1.806715933748]/2;

%Teilverstärkungen anwenden
for i=1:3
    H1(i) = H1(i) * g1;
    H2(i) = H2(i) * g2;
    H3(i) = H3(i) * g3;
    H4(i) = H4(i) * g4;
end
%Werte runden und in unseren Wertebereich verschieben
H1n = round(H1 .* 2^15);
H2n = round(H2 .* 2^15);
H3n = round(H3 .* 2^15);
H4n = round(H4 .* 2^15);

