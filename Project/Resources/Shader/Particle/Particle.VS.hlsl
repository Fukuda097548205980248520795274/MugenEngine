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
    // WVP行列
    float4x4 worldViewProjection;
    
    // ワールド行列
    float4x4 world;
    
    // ワールド行列の逆転置行列
    float4x4 worldInverseTranspose;
};
StructuredBuffer<TransformationMatrix> gTransformationMatrix : register(t0);

VertexShaderOutput main(VertexShaderInput input, uint instanceID : SV_InstanceID)
{
    VertexShaderOutput output;
    
    // 座標変換を行う
    output.position = mul(input.position, gTransformationMatrix[instanceID].worldViewProjection);
    
    // UV座標を受け取る
    output.texcoord = input.texcoord;
    
    // 法線をワールド座標に変換する
    output.normal = normalize(mul(input.normal, (float3x3) gTransformationMatrix[instanceID].worldInverseTranspose));
    
    // オブジェクトのワールド座標
    output.worldPosition = mul(input.position, gTransformationMatrix[instanceID].world).xyz;
    
    return output;
}