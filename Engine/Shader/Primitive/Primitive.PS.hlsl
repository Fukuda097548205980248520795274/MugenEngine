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
};
ConstantBuffer<Material> gMaterial : register(b0);

PixelShaderOutput main()
{
    PixelShaderOutput output;
    
    // 色の設定
    output.color = gMaterial.color;
    
    return output;
}