#include <bitset>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#define U using
U namespace std;U A=char;U B=uint8_t;U C=uint16_t;U D=int;U E=string;A*a="z\0��;��;��;��;��;��;�\r���;��;��;��;��;��;��;�\r���;��;��;��;��;��;��;��;��;�\r���;��;��;��;��;��;��;��;��;��;��;��;��;��;��;��;�\r�\0\0\0\0\r\0\0\0\0\0>\08\0	-\0\n1\0,\0\0\r~\0*\0r\0W\0t\0`\0�\0�\0�\0�\0	�	�	�\032	�	�	�\n�	X\n� \n�!\n�\"\n�#\n�$\n�%4&\n�'\n�(f)\r�*g+d,5-�.�0\r�1�;2�;3�;4�;5�;6\r�7�8�:\r�;\r�<�;>\r�A\r�B\r�C�;D�;G�;H�;I�;L�;P\r�R�;S�;Y�;Z�;\\�;^�;_�;r�;x�;y�;|\r�3�\0\0�;�������n;o��{�;�\0;�v㹋;o�]�p����\0""8�s�;�����#�,�}���ݐwA7�V��w#��ܮ�~&��}N(oq�wK�l�;�+Ӹ=�f������7���f����>�.����ퟯ&x�Wu�S���N����W��_�%��b�w����Y���巇?s7[�����R���c\0\0\0����2u~���v�Lm����_�;&��l������q���Wj���Ÿ9~ߩ�\\}m�c��m���k�ߵ�o�����v1����UU���KێoN�7�}������OPB�򲺏�����g�q��3�07�9�ce�V<���q��z�������\r�߳Ӗ������Km��~�V@\0\0G��q���8�6���x9��&��[��1��-ÿ��N�H���_qy.���6��Tǫ�?_�z�׳I�����#{왪�@o���m�Y���eUcg���|U���S���ܞ���c�Vz>W߳�qg��m��+��ž�b��W�Y�f���L���y��8������Յ˗?~	�z~�d�,u�N_�q�������Y���$�+�`����[�-�ն�~�����{c����������l՛�<�����s���T_v���Nٕ�gM祟�����?��c��o��[��d��Vٵ�.]%���{������Ҭ�i�ۏ�/��}ַ����3g��;cd�W�N[����ͯ�\\r��畯��Zq�Ǚ�������k4�\n��Ϙ��?�}�b�����v1��տW��6�}Oח�7a�<���q8��U:��U���Ҽ��|��߳�����ˏϬ�?�`;jw}�#b���ڧ1�w�³�w������m��})y��}�Ou���}�O����N3�LΓi'���qK}�����)�3�W��g�|���S~�g�v��H=���g����\0L��3n��e¥^�w�}U�X��vA �)&	�u�~t�-=�(ۈH\0\0�-�������i�f�>���;]^?o���= P�	m=�߳��q.:_ޙ�zg��k��_��V3�|���=��z��3\032�}�\n���k�?O�g�'�=���>��	$U9FSwo�\032݇��{�=Uf�V��f��c�\n�B|�߀\n��������+w�-�1��������w}}�����9E����k�q^~��L-��yFwI�Ͻ�3�3��eb�b���L��xv���{uAo�����择�[�\032�^p�H\0\0\0\0\0���:m���������8Ɩ��r1��gv��닖{y��k��7�U���R����UW����b�ϭ��vn,��_��>��Q��n��e������W�ߎ|�Ix�>��3�����hN���\0���s�\0\0Dr�\0\0d<\0 ��ŋ�J 4�n�0�/�YEu���n�����`\0�W���݁�r\032\0_оˤ�i�=��g�]���f\0\0@����5�Y�N�Q�N���\"it�SKm�uc�M���ߣ�����u�a�T\nέb?��6*���ǹ�����\0 |>����@���f�Lpg����|W\"�]�ft�?��x	1;���|[@�6SO��ͧ	ps����ʼ�O@\0?Y�9�۷,�  �HBN�֐\"H+.�\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0��@\0��CX��zd��\0\0\032o(\0N��~g~��7>�o\0?�\0\0���t�����V��B��Z�q�7v��tSN�t��`~�˔�5t\032��y� $I�\r��X���꧘�_�i�\"�V���},�K�S\\���\n�Q�`��j��f�����_��������MZ����_Ӎ:P��A*Q���뒥<�0}�\0Zױ�\\�����T�\0\0O�-{��\0w�W����7V����c��d���,�����;�*�ū���\0\0\0\0�����|9ߜe;���\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0�\\�w�]R�fS����{}U�rίĺ�Z���Y�)K}�8{o2H�H������1�gW�i���\n�$��,Ү�X_�Y�����#�wIPW;�����a��]_W���۪'�<���g����[AO/;X�Y�r�6h�����_R�V�[���m1��=��P�G�zL����Y���B7�d�쇽�������>b�F���H	$\0O�\0\0��O��)��n�o�����;��r�:B$�R��C|�0~�Li��yg����U�Đ�\0\0\0\0""7;ڭwk��'��uaS��W}'>�۔���3�Ў%����|���� �*��yh���o�����7{����5����gɳwtGx�(_�}�Y�`�g���Ҝ}��\\2�4�O��n��q�`�~)���䐢q-��)2��-��_v�?��#����z��KK�6�7;��UOP)���c�>5ӕYT�z?�@tItcX�	��5��g�g�����o/��9�v_gҾ���ڀ\0\0\0=+lph��x�#�}�o��o\0\0\0\0���D)�<\0\0\0��à���պ+H�s�w� +�Վ���hǹ@u�u��w�����L�<���\0\0\0���.`��$lI&��If�`F�t6$��ٺ����i���$\rH٠F�@��#M���旯�|*dg�o�^ת���O�3��p���G�r��\n�uo�ٛ���c���V��~@8[$HEC~���L���7��ٻ6�sX�ֶLVj��m/6N@>t�C�ޮ~��\0����E�GyjU�K6������{�zC±v�������\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0�~�;����z}�G��;顙o����R:�e����u����������WE���\0�`Eb��	��է݅>��\\u�r䯏��f�(�n[#3e��\"�x�f�7K��,������;�yA��K^L_��n���?�k�>���rcL�{��VL~�m<�����g	�+�g�RHF���m�U^������h*����ucK�)�N\r����,�����׫���H�_��Yg���{1�f�7ܮ�8ᗖ�\0��Œ�c~�y�^�c���0з�zk��0q���?�����&���U��������\r�ڷg�����6ʺn\"�ߩ���<�o�������j^^m=�t8-�����<7�Z�I�\0��C�E���t6$f|��Z���-k��y��tx��k[�Ncۻ���f���|g;xݗ߳���'�{e����H�F}��/����e0�5�j}K��g��@<��L���{����Yi��f�;���ҁ���_�'y9N�d��ۂ��wvq�*���h�$�ʴ���ϭ����3����ww���T\0&�[\"\0j���x�zC���m�������b�N7�['y�z��p���;�nIE&U�'�����t�Y�v9�0�D��\0w���v]�\0\0\0\0\0\0\0\0\0\0\0'�j�n��A��������Uؓ��Y��nM�&Ｉ��\r|��m����Y<Ԓb���qp�&>����ot���R���W�C�N���R�t�����e�D�C�����Oh`�N���u\0e�۽�ޗ��`'ե����q�+/�]��3���:�o�9�{5m�2���\0x�\r;'�������p��ZG������\0����{k���g�DͻW���q+�3��������<�kO������4�V�gA����ػ�jz�#�3}�bOMj��jn��Si�7϶�/\n�=)Y�Ծ�o�cJ{��h�\0R��<�8�Ζ����S�v%�1�tĤ�k9���c�����Ѡ��<+*5��ǂO��X���uESP\0��ZtSh�(�{��p�^��f��~�TG���>u�o�ӱ<�\"z^��7f����}������/�<D��ڥ=M<eK�)w������3�{A�'4�s�i+=���o��T��mq:��m@�(7哌���\0.n�\0��H�r�9=���˯�~?�ӧNE+�Æ����T��삸н�f5���̳���-ՐQ��=\0�\0k�����p��<�I�O���uY������!�6uYe��׻kٯ��:�q��'�L��M+���x�)��?�<��d����nm0�$����A���Ӑu@�`��8@-S�OH9��@��\nA a�x���O`����\0\0\0\0\0\0\0\0\0\0\0\0\0\09��1�b0\0r�a! Dq\0�\0u���mv�	�b�9�WkG���[�:{�n�[�ڸ�[9�)�����Kl�5s������\\}3e��Q�[F�7�Y~�73���c��k�M�:�=����{�s������/g1�L�7u�ԑT%�M��sk��w��n���) gt@�/�����=�3��?ɿ�k w�����{\r=k���������\0�C��N|y����Y�®��s;qzM��2�����/�=�k;�_�\n��ߥ��˃���	RXE��9����>@�h\032�o���m۹gs�7@�H\rkMӻ����&�}�]��K��3M�񘧻�^㩶V4��.�]~�Ǻ�lD�I$$ �d�<5��$\0)D_�n�\"/��3Y�xA.���`��Av_��,�\0f��=\0�5s{���}Ou��+汯��vÃ�\0:��\0\0Y�o��1�<ߵ�����+o��\0\0`�\"�D�hv������%w;캤�Ӽ���a�Si�M���ǚ~��}~�_�;���";D main(){A*b=a;E c;map<pair<A,C>,A>j;C s=(C&)b[0];b+=2;for(C i=0;i<s*4;i+=4)j[{b[1],(C&)b[2]}]=b[0],b+=4;D h=(D&)b[0];b+=4;bitset<8>l=*b++;A o=7;A k=0;C n=0;while(h>0){++k;n<<=1;n+=l.test(o--);if(j.count({k,n})>0){c+=j[{k,n}];k=0;n=0;}--h;if(o==-1&&h>0)o=7,l=*b++;}E d;E q(256,0);for(D i=0;i<256;++i)q[i]=i;for(B c:c){A r=q[255-c];d+=r;q.erase(255-c,1);q+=r;}map<B,D>u;map<B,D>t;vector<D>v;C w=(C&)d[0];d=d.substr(2);for(B c:d)v.push_back(u[c]++);D x=0;for(auto p:u)t[p.first]=x,x+=p.second;auto y=d.size();E e(y,'=');D m=w;for(auto i=y-1;(i+y)>=y;--i)e[i]=d[m],m=v[m]+t[e[i]];A*z="ACGT";for(B c:e)cout<<z[c>>6]<<z[(c&48)>>4]<<z[(c&12)>>2]<<z[c&3];}
