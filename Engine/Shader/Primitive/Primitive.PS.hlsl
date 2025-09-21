#include "Primitive.hlsli"

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

// マテリアル設定
struct Material
{
    // 色
    float4 color;
    
    // ライティング有効化
    int enableLighting;
    
    // ハーフランバート有効化
    int enableHalfLambert;
    
    // UVトランスフォーム
    float4x4 uvTransform;
};
ConstantBuffer<Material> gMaterial : register(b0);

// 平行光源設定
struct DirectionalLight
{
    // 色
    float4 color;
    
    // 向き
    float3 direction;
    
    // 輝度
    float intensity;
};
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);



PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    // UV座標を座標変換する
    float4 transformedUV = mul(float4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
    
    // テクスチャの色
    float4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    
    // ライティング有効
    if (gMaterial.enableLighting != 0)
    {
        if (gMaterial.enableHalfLambert != 0)
        {
            // ハーフランバート有効
            
            // 光と法線の内積
            float NdotL = dot(normalize(input.normal), -gDirectionalLight.direction);
            
            // なだらかにする
            float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
            output.color.rgb = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * gDirectionalLight.intensity;
            output.color.a = gMaterial.color.a * textureColor.a;

        }
        else
        {
            // ハーフランバート無効
            
            // 光と法線の方向が近ければ明るい
            float cos = saturate(dot(normalize(input.normal), -gDirectionalLight.direction));
            output.color.rgb = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * gDirectionalLight.intensity;
            output.color.a = gMaterial.color.a * textureColor.a;
        }
    }
    else
    {
        // ライティング無効
        
        // 色の設定
        output.color = gMaterial.color * textureColor;
    }
    
    return output;
}