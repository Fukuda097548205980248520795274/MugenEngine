#include "Primitive.hlsli"

// 入力頂点
struct VertexShaderInput
{
    float4 position : POSITION0;
};

// 座標変換行列
struct TransformationMatrix
{
    float4x4 worldViewProjection;
};
ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);

VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    
    // 座標変換を行う
    output.position = mul(input.position, gTransformationMatrix.worldViewProjection);
    
    return output;
}