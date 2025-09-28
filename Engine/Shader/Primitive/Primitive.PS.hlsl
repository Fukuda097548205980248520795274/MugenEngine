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
    
    // スペキュラー有効化
    int enableSpecular;
    
    // 光沢度
    float shininess;
    
    // UVトランスフォーム
    float4x4 uvTransform;
};
ConstantBuffer<Material> gMaterial : register(b0);

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);


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
StructuredBuffer<DirectionalLight> gDirectionalLight : register(t1);

// 平行光源数
struct NumDirectionalLight
{
    // 数
    uint num;
};
ConstantBuffer<NumDirectionalLight> gNumDirectionalLight : register(b1);

// カメラデータ
struct Camera
{
    float3 worldPosition;
};
ConstantBuffer<Camera> gCamera : register(b2);



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
        // カメラへの方向を算出
        float3 toEye = normalize(gCamera.worldPosition - input.worldPosition);
        
        
        // 平行光源の拡散反射
        float3 directionalLightDiffuse = float3(0.0f, 0.0f, 0.0f);
        
        // 平行光源の鏡面反射
        float3 directionalLightSpecular = float3(0.0f, 0.0f, 0.0f);
        
        
        // ハーフランバート有効
        if (gMaterial.enableHalfLambert != 0)
        {
            for (uint directionalLightIndex = 0; directionalLightIndex < gNumDirectionalLight.num; ++directionalLightIndex)
            {
                // 光と法線の内積
                float NdotL = dot(normalize(input.normal), -gDirectionalLight[directionalLightIndex].direction);
            
                // なだらかにする
                float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
                
                // 光の拡散反射を加算する
                directionalLightDiffuse += gDirectionalLight[directionalLightIndex].color.rgb * cos * gDirectionalLight[directionalLightIndex].intensity;
                
                // スペキュラー有効
                if (gMaterial.enableSpecular != 0)
                {
                    // 入射光の反射ベクトル
                    float3 reflectLight = reflect(gDirectionalLight[directionalLightIndex].direction, normalize(input.normal));

                    // カメラと反射ベクトルの内積
                    float RdotE = dot(reflectLight, toEye);
                    
                    // 反射の強度
                    float specularPow = pow(saturate(RdotE), gMaterial.shininess);
                    
                    // 光の鏡面反射を加算する
                    directionalLightSpecular +=
                    gDirectionalLight[directionalLightIndex].color.rgb * gDirectionalLight[directionalLightIndex].intensity * specularPow * float3(1.0f, 1.0f, 1.0f);

                }
            }

        }
        else
        {
            // ハーフランバート無効
            
            for (uint directionalLightIndex = 0; directionalLightIndex < gNumDirectionalLight.num; ++directionalLightIndex)
            {
                // なだらかにする
                float cos = saturate(dot(normalize(input.normal), -gDirectionalLight[directionalLightIndex].direction));
                
                // 光の拡散反射を加算する
                directionalLightDiffuse += gDirectionalLight[directionalLightIndex].color.rgb * cos * gDirectionalLight[directionalLightIndex].intensity;
                
                // スペキュラー有効
                if (gMaterial.enableSpecular != 0)
                {
                     // 入射光の反射ベクトル
                    float3 reflectLight = reflect(gDirectionalLight[directionalLightIndex].direction, normalize(input.normal));

                    // カメラと反射ベクトルの内積
                    float RdotE = dot(reflectLight, toEye);
                    
                    // 反射の強度
                    float specularPow = pow(saturate(RdotE), gMaterial.shininess);
                    
                    // 光の鏡面反射を加算する
                    directionalLightSpecular +=
                    gDirectionalLight[directionalLightIndex].color.rgb * gDirectionalLight[directionalLightIndex].intensity * specularPow * float3(1.0f, 1.0f, 1.0f);

                }
            }
        }
        
        
        // 色を合成する
        output.color.rgb = gMaterial.color.rgb * textureColor.rgb * (directionalLightDiffuse + directionalLightSpecular);
        output.color.a = gMaterial.color.a * textureColor.a;
    }
    else
    {
        // ライティング無効
        
        // 色の設定
        output.color = gMaterial.color * textureColor;
    }
    
    // a = 0は描画しない
    if (output.color.a == 0.0f || textureColor.a == 0.0f)
    {
        discard;
    }
    
    return output;
}