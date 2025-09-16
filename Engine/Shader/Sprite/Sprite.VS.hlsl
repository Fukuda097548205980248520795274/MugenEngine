#include "Sprite.hlsli"

// 入力頂点
struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
};

// 座標変換行列
struct TransformationMatrix
{
    float4x4 worldViewProjection;
};
ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);

VertexShaderOutput main(VertexShaderInput input)
{
    // 出力頂点
    VertexShaderOutput output;
    
    output.position = mul(input.position, gTransformationMatrix.worldViewProjection);
    output.texcoord = input.texcoord;
    
    return output;
}