using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FristPersonGunController : MonoBehaviour
{
    // 自動か手動か
    public enum ShootMode
    {
        AUTO,
        SEMIAUTO
    };

    public bool _shootEnabled = true;

    [SerializeField]
    ShootMode _shootMode = ShootMode.AUTO;       // 自動化制御

    [SerializeField]
    int _maxAmmo = 100;                          // 弾の最大数

    [SerializeField]
    int _damage = 1;                             // 弾のﾀﾞﾒｰｼﾞ

    [SerializeField]
    float _shootInterval = 0.15f;                // 次弾が出るまでの間隔

    [SerializeField]
    float _shootRange = 50;                      // 飛距離

    [SerializeField]
    GameObject _muzzleFlashPrefab;               // 撃った時のｴﾌｪｸﾄ

    [SerializeField]
    Vector3 _muzzleFlashScale;                   // ﾌﾗｯｼｭｴﾌｪｸﾄの大きさ

    [SerializeField]
    GameObject _hitEffectPrefab;                 // ﾋｯﾄｴﾌｪｸﾄ用

    // 
    bool _shooting = false;                      // 今撃っているかどうか
    int ammo;
    GameObject muzzleFlash;
    GameObject hitEffect;

    public int Ammo
    {
        set
        {
            ammo = Mathf.Clamp(value, 0, _maxAmmo);
        }
        get
        {
            return ammo;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        InitGun();
    }

    // Update is called once per frame
    void Update()
    {
        if(_shootEnabled & ammo > 0 & GetInput())
        {
            StartCoroutine(ShootTimer());
        }
    }

    // 初期設定
    void InitGun()
    {
        Ammo = _maxAmmo;
    }

    bool GetInput()
    {
        // ｵｰﾄだったら全部返す
        switch(_shootMode)
        {
            case ShootMode.AUTO:
                return Input.GetMouseButton(0);

            case ShootMode.SEMIAUTO:
                return Input.GetMouseButtonDown(0);
        }

        return false;
    }

    IEnumerator ShootTimer()
    {
        if (!_shooting)
        {
            _shooting = true;

            // ﾏｽﾞﾙﾌﾗｯｼｭON
            if (_muzzleFlashPrefab != null)
            {
                if (muzzleFlash != null)
                {
                    muzzleFlash.SetActive(true);
                }
                else
                {
                    // 設定します
                    muzzleFlash = Instantiate(_muzzleFlashPrefab, transform.position, transform.rotation);
                    muzzleFlash.transform.SetParent(gameObject.transform);
                    muzzleFlash.transform.localScale = _muzzleFlashScale;
                }
            }


            Shoot();

            yield return new WaitForSeconds(_shootInterval);

            // ﾏｽﾞﾙﾌﾗｯｼｭOFF
            if (muzzleFlash != null)
            {
                muzzleFlash.SetActive(false);
            }

            // ﾋｯﾄｴﾌｪｸﾄOFF
            if (hitEffect != null)
            {
                if (hitEffect.activeSelf)
                {
                    muzzleFlash.SetActive(false);
                }
            }

            _shooting = false;
        }
        else
        {
            yield return null;
        }
    }

    void Shoot()
    {
        Ray ray = new Ray(transform.position, transform.forward);
        RaycastHit hit;

        if (Physics.Raycast(ray, out hit, _shootRange))
        {
            // ﾋｯﾄｴﾌｪｸﾄON
            // 取得できていなかったらnullなはず
            if (_hitEffectPrefab != null)
            {
                if (hitEffect != null)
                {
                    // あたった位置にｴﾌｪｸﾄを移動 
                    hitEffect.transform.position = hit.point;
                    hitEffect.transform.rotation = Quaternion.FromToRotation(Vector3.forward, hit.normal);
                    hitEffect.SetActive(true);
                }
                else
                {
                    // 取得しますよ
                    hitEffect = Instantiate(_hitEffectPrefab, hit.point, Quaternion.identity);
                }
            }

            // ﾀﾞﾒｰｼﾞ
        }
        Ammo--;
    }
}
