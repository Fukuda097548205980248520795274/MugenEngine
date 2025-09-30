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

// ポイントライト設定
struct PointLight
{
    // 色
    float4 color;
    
    // 位置
    float3 position;
    
    // 輝度
    float intensity;
    
    // ライトの届く最大距離
    float radius;
    
    // 減衰率
    float decay;
};
StructuredBuffer<PointLight> gPointLight : register(t2);

// ポイントライト数
struct NumPointLight
{
    // 数
    uint num;
};
ConstantBuffer<NumPointLight> gNumPointLight : register(b3);

// スポットライト設定
struct SpotLight
{
    // 色
    float4 color;
    
    // 位置
    float3 position;
    
    // 輝度
    float intensity;
    
    // 方向
    float3 direction;
    
    // ライトの届く距離
    float distance;
    
    // 減衰率
    float decay;
    
    // 光の当たる角度
    float cosAngle;
    
    // フォールオフ開始値
    float cosFalloffStart;
};
StructuredBuffer<SpotLight> gSpotLight : register(t3);

// スポットライト数
struct NumSpotLight
{
    // 数
    uint num;
};
ConstantBuffer<NumSpotLight> gNumSpotLight : register(b4);




// 平行光源の拡散反射
float3 CreateDirectionalLightDiffuse(uint directionalLightIndex, VertexShaderOutput input)
{
    // ハーフランバート有効
    if (gMaterial.enableHalfLambert != 0)
    {
        // 光と法線の内積
        float NdotL = dot(normalize(input.normal), -gDirectionalLight[directionalLightIndex].direction);
            
        // なだらかにする
        float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
                
        // 光の拡散反射を返却する
        return gDirectionalLight[directionalLightIndex].color.rgb * cos * gDirectionalLight[directionalLightIndex].intensity;
    }
    else
    {
        // なだらかにする
        float cos = saturate(dot(normalize(input.normal), -gDirectionalLight[directionalLightIndex].direction));
                
        // 光の拡散反射を返却する
        return gDirectionalLight[directionalLightIndex].color.rgb * cos * gDirectionalLight[directionalLightIndex].intensity;
    }
}

// 平行光源の鏡面反射
float3 CreateDirectionalLightSpecular(uint directionalLightIndex , float3 toEye , VertexShaderOutput input)
{
    // 反射の強度
    float specularPow = 0.0f;
                    
    // ブリンフォン有効
    if (gMaterial.enableBlinnPhong != 0)
    {
        // ハーフベクトル
        float3 halfVector = normalize(-gDirectionalLight[directionalLightIndex].direction + toEye);

        // 法線とハーフベクトルの内積
        float NdotH = dot(normalize(input.normal), halfVector);

        specularPow = pow(saturate(NdotH), gMaterial.shininess);

    }
    else
    {
        // ブリンフォン無効
        
        // 入射光の反射ベクトル
        float3 reflectLight = reflect(gDirectionalLight[directionalLightIndex].direction, normalize(input.normal));

        // カメラと反射ベクトルの内積
        float RdotE = dot(reflectLight, toEye);

        specularPow = pow(saturate(RdotE), gMaterial.shininess);
    }

    return gDirectionalLight[directionalLightIndex].color.rgb * gDirectionalLight[directionalLightIndex].intensity * specularPow * float3(1.0f, 1.0f, 1.0f);
}

// ポイントライトの拡散反射
float3 CreatePointLightDiffuse(uint pointLightIndex, float3 pointLightDirection, VertexShaderOutput input)
{    
    // ハーフランバート有効
    if (gMaterial.enableHalfLambert != 0)
    {
        // 光と法線の内積
        float NdotL = dot(normalize(input.normal), -pointLightDirection);
            
        // なだらかにする
        float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
                
        // 光の拡散反射を返却する
        return gPointLight[pointLightIndex].color.rgb * cos * gPointLight[pointLightIndex].intensity;
    }
    else
    {
        // なだらかにする
        float cos = saturate(dot(normalize(input.normal), -pointLightDirection));
                
        // 光の拡散反射を返却する
        return gPointLight[pointLightIndex].color.rgb * cos * gPointLight[pointLightIndex].intensity;
    }
}

// ポイントライトの鏡面反射
float3 CreatePointLightSpecular(uint pointLightIndex, float3 pointLightDirection, float3 toEye , VertexShaderOutput input)
{
    // 反射の強度
    float specularPow = 0.0f;
                    
    // ブリンフォン有効
    if (gMaterial.enableBlinnPhong != 0)
    {
        // ハーフベクトル
        float3 halfVector = normalize(-pointLightDirection + toEye);

        // 法線とハーフベクトルの内積
        float NdotH = dot(normalize(input.normal), halfVector);

        specularPow = pow(saturate(NdotH), gMaterial.shininess);

    }
    else
    {
        // ブリンフォン無効
        
        // 入射光の反射ベクトル
        float3 reflectLight = reflect(-pointLightDirection, normalize(input.normal));

        // カメラと反射ベクトルの内積
        float RdotE = dot(reflectLight, toEye);

        specularPow = pow(saturate(RdotE), gMaterial.shininess);
    }

    return gPointLight[pointLightIndex].color.rgb * gPointLight[pointLightIndex].intensity * specularPow * float3(1.0f, 1.0f, 1.0f);
}

// スポットライトの拡散反射
float3 CreateSpotLightDiffuse(uint spotLightIndex, float3 spotLightDirectionOnSurface, VertexShaderOutput input)
{
    // ハーフランバート有効
    if (gMaterial.enableHalfLambert != 0)
    {
        // 光と法線の内積
        float NdotL = dot(normalize(input.normal), -spotLightDirectionOnSurface);
            
        // なだらかにする
        float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
                
        // 光の拡散反射を返却する
        return gSpotLight[spotLightIndex].color.rgb * cos * gSpotLight[spotLightIndex].intensity;
    }
    else
    {
        // なだらかにする
        float cos = saturate(dot(normalize(input.normal), -spotLightDirectionOnSurface));
                
        // 光の拡散反射を返却する
        return gSpotLight[spotLightIndex].color.rgb * cos * gSpotLight[spotLightIndex].intensity;
    }
}

// スポットライトの拡散反射
float3 CreateSpotLightSpecular(uint spotLightIndex, float3 spotLightDirectionOnSurface, float3 toEye, VertexShaderOutput input)
{
    // 反射の強度
    float specularPow = 0.0f;
                    
    // ブリンフォン有効
    if (gMaterial.enableBlinnPhong != 0)
    {
        // ハーフベクトル
        float3 halfVector = normalize(-spotLightDirectionOnSurface + toEye);

        // 法線とハーフベクトルの内積
        float NdotH = dot(normalize(input.normal), halfVector);

        specularPow = pow(saturate(NdotH), gMaterial.shininess);

    }
    else
    {
        // ブリンフォン無効
        
        // 入射光の反射ベクトル
        float3 reflectLight = reflect(-spotLightDirectionOnSurface, normalize(input.normal));

        // カメラと反射ベクトルの内積
        float RdotE = dot(reflectLight, toEye);

        specularPow = pow(saturate(RdotE), gMaterial.shininess);
    }

    return gSpotLight[spotLightIndex].color.rgb * gSpotLight[spotLightIndex].intensity * specularPow * float3(1.0f, 1.0f, 1.0f);
}


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
        
        
        ///
        /// 平行光源
        ///
        
        // 平行光源の拡散反射
        float3 directionalLightDiffuse = float3(0.0f, 0.0f, 0.0f);
        
        // 平行光源の鏡面反射
        float3 directionalLightSpecular = float3(0.0f, 0.0f, 0.0f);

        // 使用している平行光源から値を取得する
        for (uint directionalLightIndex = 0; directionalLightIndex < gNumDirectionalLight.num; ++directionalLightIndex)
        {
            // 光の拡散反射を加算する
            directionalLightDiffuse += CreateDirectionalLightDiffuse(directionalLightIndex, input);
                
            // スペキュラー有効
            if (gMaterial.enableSpecular != 0)
            {
                // 光の鏡面反射を加算する
                directionalLightSpecular += CreateDirectionalLightSpecular(directionalLightIndex, toEye, input);
            }
        }
        
        
        ///
        /// ポイントライト
        ///
        
        // ポイントライトの拡散反射
        float3 pointLightDiffuse = float3(0.0f, 0.0f, 0.0f);
        
        // ポイントライトの鏡面反射
        float3 pointLightSpecular = float3(0.0f, 0.0f, 0.0f);
        
        // 使用しているポイントライトから値を取得する
        for (uint pointLightIndex = 0; pointLightIndex < gNumPointLight.num; ++pointLightIndex)
        {
            // ポイントライトの光の向きを取得する
            float3 pointLightDirection = normalize(input.worldPosition - gPointLight[pointLightIndex].position);
            
            // ポイントライトの距離
            float distance = length(gPointLight[pointLightIndex].position - input.worldPosition);
            
            // 逆二乗則による減衰係数
            float factor = pow(saturate(-distance / gPointLight[pointLightIndex].radius + 1.0f), gPointLight[pointLightIndex].decay);
            
            // 拡散反射を加算する
            pointLightDiffuse += CreatePointLightDiffuse(pointLightIndex, pointLightDirection, input) * factor;

            // スペキュラー有効
            if (gMaterial.enableSpecular != 0)
            {
                // 鏡面反射を加算する
                pointLightSpecular += CreatePointLightSpecular(pointLightIndex, pointLightDirection, toEye, input) * factor;

            }
        }
        
        
        ///
        /// スポットライト
        ///
        
        // スポットライトの拡散反射
        float3 spotLightDiffuse = float3(0.0f, 0.0f, 0.0f);
        
        // スポットライトの鏡面反射
        float3 spotLightSpecular = float3(0.0f, 0.0f, 0.0f);
        
        // 使用しているスポットライトから値を取得する
        for (uint spotLightIndex = 0; spotLightIndex < gNumSpotLight.num; ++spotLightIndex)
        {
            // スポットライトの光の向きを取得する
            float3 spotLightDirectionOnSurface = normalize(input.worldPosition - gSpotLight[spotLightIndex].position);
            
            
            // 光の当たる角度
            float cosAngle = dot(spotLightDirectionOnSurface, gSpotLight[spotLightIndex].direction);
            
            // フォールオフ
            float falloffFactor =
            saturate((cosAngle - gSpotLight[spotLightIndex].cosAngle) / (gSpotLight[spotLightIndex].cosFalloffStart - gSpotLight[spotLightIndex].cosAngle));
            
            
            // ポイントライトの距離
            float distance = length(gSpotLight[spotLightIndex].position - input.worldPosition);
            
            // 逆二乗則による減衰係数
            float factor = pow(saturate(-distance / gSpotLight[spotLightIndex].distance + 1.0f), gSpotLight[spotLightIndex].decay);
            
            // 拡散反射を加算する
            spotLightDiffuse += CreateSpotLightDiffuse(spotLightIndex, spotLightDirectionOnSurface, input) * factor * falloffFactor;
            
            // スペキュラー有効
            if (gMaterial.enableSpecular != 0)
            {
                // 鏡面反射の加算する
                spotLightSpecular += CreateSpotLightSpecular(spotLightIndex, spotLightDirectionOnSurface, toEye, input) * factor * falloffFactor;
            }
        }
        
        
        // 色を合成する
        output.
            color.rgb = gMaterial.color.rgb * textureColor.rgb *
        (directionalLightDiffuse + directionalLightSpecular + pointLightDiffuse + pointLightSpecular + spotLightDiffuse + spotLightSpecular);
        
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