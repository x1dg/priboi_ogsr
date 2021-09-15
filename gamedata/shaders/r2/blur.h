#ifndef BLUR
#define BLUR
float2 TexelKernelh[13];
float4 gl_TexCoord[10];
float BlurWeights[13];
float3 gaussblur(v2p I,float blur) { 
float2 center=I.tc0;
half3 img=tex2D(s_image,center);
float d=blur*100.0-300.0;
int i=0;
TexelKernelh[0]=float2(0,-6);
TexelKernelh[1]=float2(0,-5);
TexelKernelh[2]=float2(0,-4);
TexelKernelh[3]=float2(0,-3);
TexelKernelh[4]=float2(0,-2);
TexelKernelh[5]=float2(0,-1);
TexelKernelh[6]=float2(0,0);
TexelKernelh[7]=float2(0,1);
TexelKernelh[8]=float2(0,2);
TexelKernelh[9]=float2(0,3);
TexelKernelh[10]=float2(0,4);
TexelKernelh[11]=float2(0,5);
TexelKernelh[12]=float2(0,6);
BlurWeights[0]=0.002216;
BlurWeights[1]=0.008764;
BlurWeights[2]=0.026995;
BlurWeights[3]=0.064759;
BlurWeights[4]=0.120985;
BlurWeights[5]=0.176033;
BlurWeights[6]=0.199471;
BlurWeights[7]=0.176033;
BlurWeights[8]=0.120985;
BlurWeights[9]=0.064759;
BlurWeights[10]=0.026995;
BlurWeights[11]=0.008764;
BlurWeights[12]=0.002216;
float3 sum=tex2D(s_image,center).rgb; 
half4 coord=tex2D(s_position,center);
float contrib=1.h;
for (int i=0; i < 13; i++) { 
float2 tap=center.xy+TexelKernelh[i].yx/d;
float3 tap_color=tex2D(s_image,tap).rgb*BlurWeights[i]; 
sum+=tap_color;
contrib++;
}
for (int i=0; i < 13; i++) { 
float2 tap=center.xy+TexelKernelh[i].xy/d;
float3 tap_color=tex2D(s_image,tap).rgb*BlurWeights[i]; 
sum+=tap_color;
contrib++;
}
contrib=(0.7-0.29)*100.h;
return sum/contrib;
}
float3 simpleblur(v2p I,float factor) {
float2 center=I.tc0;
float dx=factor*.5f/1024.f;
float dy=factor*.5f/768.f;
return
(4*tex2D(s_image,center).rgb+2*tex2D(s_image,center+float2(dx,0)).rgb+2*tex2D(s_image,center+float2(-dx,0)).rgb+2*tex2D(s_image,center+float2(0,dy)).rgb+2*tex2D(s_image,center+float2(0,-dy)).rgb+1*tex2D(s_image,center+float2(dx,dy)).rgb+1*tex2D(s_image,center+float2(dx,-dy)).rgb+1*tex2D(s_image,center+float2(-dx,dy)).rgb+1*tex2D(s_image,center+float2(-dx,-dy)).rgb)/16;
}
float3 classicblur(float2 cent,float3 sum,float factor,int samples) {
float2 bias=float2(.5f/1024.f,.5f/768.f);
float2 scale=bias*factor;
float2 o [48];
o[0]=float2(-0.326212f,-0.405810f)*scale;
o[1]=float2(-0.840144f,-0.073580f)*scale;
o[2]=float2(-0.695914f,0.457137f)*scale;
o[3]=float2(-0.203345f,0.620716f)*scale;
o[4]=float2(0.962340f,-0.194983f)*scale;
o[5]=float2(0.473434f,-0.480026f)*scale;
o[6]=float2(0.519456f,0.767022f)*scale;
o[7]=float2(0.185461f,-0.893124f)*scale;
o[8]=float2(0.507431f,0.064425f)*scale;
o[9]=float2(0.896420f,0.412458f)*scale;
o[10]=float2(-0.321940f,-0.932615f)*scale;
o[11]=float2(-0.791559f,-0.597710f)*scale; 
float contrib=1.h;
int j=0;
for (int i=0;i<samples;i++){ 
float2 tap=cent+o[j];
float3 tap_color=tex2D(s_image,tap).rgb;
sum+=tap_color;
contrib++;
j++; if (j > 11) { j=0; }
}
return sum;
}
#endif