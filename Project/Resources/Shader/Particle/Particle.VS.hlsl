#include "Particle.hlsli"

// 入力頂点
struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
};

// 座標変換行列
struct ParticleForGPU
{
    // WVP行列
    float4x4 worldViewProjection;
    
    // ワールド行列
    float4x4 world;
    
    // 色
    float4 color;
};
StructuredBuffer<ParticleForGPU> gParticleForGPU : register(t0);

VertexShaderOutput main(VertexShaderInput input, uint instanceID : SV_InstanceID)
{
    VertexShaderOutput output;
    
    // 座標変換を行う
    output.position = mul(input.position, gParticleForGPU[instanceID].worldViewProjection);
    
    // UV座標を受け取る
    output.texcoord = input.texcoord;
    
    // 色を受け取る
    output.color = gParticleForGPU[instanceID].color;
    
    return output;
}