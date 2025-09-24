#include "Particle.hlsli"

// 入力頂点
struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
};

// 座標変換行列
struct TransformationMatrix
{
    float4x4 worldViewProjection;
    float4x4 world;
};
StructuredBuffer<TransformationMatrix> gTransformationMatrices : register(t0);

VertexShaderOutput main(VertexShaderInput input, uint instanceId : SV_InstanceID)
{
    VertexShaderOutput output;
    
    // 座標変換を行う
    output.position = mul(input.position, gTransformationMatrices[instanceId].worldViewProjection);
    
    // UV座標を受け取る
    output.texcoord = input.texcoord;
    
    // 法線をワールド座標に変換する
    output.normal = normalize(mul(input.normal, (float3x3) gTransformationMatrices[instanceId].world));
    
    return output;
}