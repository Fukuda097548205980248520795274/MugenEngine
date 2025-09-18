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
    
    // テクスチャの色
    float4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    
    // ライティング有効
    if (gMaterial.enableLighting != 0)
    {
        float cos = saturate(dot(normalize(input.normal), -gDirectionalLight.direction));
        output.color = gMaterial.color * textureColor * gDirectionalLight.color * cos * gDirectionalLight.intensity;

    }
    else
    {
        // ライティング無効
        
        // 色の設定
        output.color = gMaterial.color * textureColor;
    }
    
    return output;
}