function OnMdConnectionStatus(sender,arg)

import QuantBox.XAPI.*;

global md;

disp('MD')
% �������ӻر�
disp(arg.status);

switch arg.status
    case QuantBox.ConnectionStatus.Disconnected
        % ��ӡ������Ϣ
        disp(Extensions_GBK.ErrorMsg(arg.userLogin));
    case QuantBox.ConnectionStatus.Done
        % �������飬֧��","��";"�ָ�
        md.Subscribe('IF1502;IF1503,IF1506','');
end

end
