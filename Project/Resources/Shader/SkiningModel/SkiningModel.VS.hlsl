
// 入力頂点
struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float4 weight : WEIGHT0;
    int4 index : INDEX0;
};

// 出力頂点
struct VertexShaderOutput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 worldPosition : POSITION0;
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
ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);

struct Well
{
    float4x4 skeletonSpaceMatrix;
    float4x4 skeletonSpaceInverseTransposeMatrix;
};
StructuredBuffer<Well> gMatrixPalette : register(t0);

struct Skinned
{
    float4 position;
    float3 normal;
};

// スキニング
Skinned Skinning(VertexShaderInput input)
{
    Skinned skinned;
    
    // 位置の変換を行う
    skinned.position = mul(input.position, gMatrixPalette[input.index.x].skeletonSpaceMatrix) * input.weight.x;
    skinned.position += mul(input.position, gMatrixPalette[input.index.y].skeletonSpaceMatrix) * input.weight.y;
    skinned.position += mul(input.position, gMatrixPalette[input.index.z].skeletonSpaceMatrix) * input.weight.z;
    skinned.position += mul(input.position, gMatrixPalette[input.index.w].skeletonSpaceMatrix) * input.weight.w;
    
    // 1.0fを入れる
    skinned.position.w = 1.0f;
    
    
    // 法線の変換を行う
    skinned.normal = mul(input.normal, (float3x3) gMatrixPalette[input.index.x].skeletonSpaceInverseTransposeMatrix) * input.weight.x;
    skinned.normal += mul(input.normal, (float3x3) gMatrixPalette[input.index.y].skeletonSpaceInverseTransposeMatrix) * input.weight.y;
    skinned.normal += mul(input.normal, (float3x3) gMatrixPalette[input.index.z].skeletonSpaceInverseTransposeMatrix) * input.weight.z;
    skinned.normal += mul(input.normal, (float3x3) gMatrixPalette[input.index.w].skeletonSpaceInverseTransposeMatrix) * input.weight.w;
    skinned.normal = normalize(skinned.normal);
    
    return skinned;
}


VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    
    // スキニング
    Skinned skinning = Skinning(input);
    
    
    // 座標変換を行う
    output.position = mul(skinning.position, gTransformationMatrix.worldViewProjection);
    
    // UV座標を受け取る
    output.texcoord = input.texcoord;
    
    // 法線をワールド座標に変換する
    output.normal = normalize(mul(skinning.normal, (float3x3) gTransformationMatrix.worldInverseTranspose));
    
    // オブジェクトのワールド座標
    output.worldPosition = mul(skinning.position, gTransformationMatrix.world).xyz;
    
    return output;
}