def gcd(a, b):
    if(b==0):
        return a
    else:
        return gcd(b, a%b)
    
def power(a,p,mod):
    res= 1
    for i in range(int(p)):
        res = res*a
        res = res%mod
    return res

p = 656692050181897513638241554199181923922955921760928836766304161790553989228223793461834703506872747071705167995972707253940099469869516422893633357693
q = 204616454475328391399619135615615385636808455963116802820729927402260635621645177248364272093977747839601125961863785073671961509749189348777945177811
n = p*q
phi = (p-1)*(q-1)

new_e = 10**7
e = 10**7
#print(can_e)
while(new_e < phi):
    cal_gcd = gcd(new_e, phi)
    if(cal_gcd==1):
        e = new_e
        break
    else:
        new_e = new_e + 1

print("E: ", e)

k = 1
d = 1
while(k < 10**7):
    j = (phi*k) + 1
    if(j%e==0):
        d = j//e
        break
    k = k + 1

print("D: ", d)

msg = 60**10
print("MSG: ",msg)

cipher= pow(msg, d, n)
print("Cipher: ",cipher)

decrypted = pow(cipher,e,n)
print("Decypted: ",decrypted)

if(msg == decrypted):
    print("Valid")
else:
    print("Invalid")

