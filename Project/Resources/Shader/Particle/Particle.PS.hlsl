#include "Particle.hlsli"

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
    
    // スペキュラー有効化
    int enableSpecular;
    
    // ブリンフォン有効化
    int enableBlinnPhong;
    
    // 光沢度
    float shininess;
    
    // UVトランスフォーム
    float4x4 uvTransform;
};
ConstantBuffer<Material> gMaterial : register(b0);

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    // UV座標を座標変換する
    float4 transformedUV = mul(float4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
    
    // テクスチャの色
    float4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    
    // 色を乗算する
    output.color = gMaterial.color * textureColor * input.color;
    
    // a = 0は描画しない
    if (output.color.a == 0.0f)
    {
        discard;
    }
    
    return output;
}