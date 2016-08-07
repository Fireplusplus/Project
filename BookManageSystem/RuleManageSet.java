import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;
public class RuleManageSet implements MouseListener{
	public JFrame frame;

	public JTextField tterm;
	public JLabel lterm;
	public JTextField tnumbers;
	public JLabel lnumbers;
	public JTextField trenew;
	public JLabel lrenew;
	public JTextField tfine;
	public JLabel lfine;
	
	public JButton set;
	public JButton exit_;
	public static int ctypeno;
	public static int rtypeno;
	public Connection conn;
	public Statement st;
	
	public RuleManageSet(int ctypeno,int rtypeno)
	{	this.ctypeno=ctypeno;
		this.rtypeno=rtypeno;
		frame=new JFrame();
		frame.setSize(500,350);
		frame.setTitle("Login/Manage/RuleManage/Set");
		frame.setLayout(null);
		
		set=new JButton();
		set.setSize(60,30);
		set.setText("修改");
		set.setLocation(100,250);
		frame.add(set);
		set.addMouseListener(this);
		exit_=new JButton();
		exit_.setSize(60,30);
		exit_.setText("退出");
		exit_.setLocation(280,250);
		frame.add(exit_);
		exit_.addMouseListener(this);
		
		tterm=new JTextField();
		tterm.setSize(200,30);
		tterm.setLocation(180,50);
		frame.add(tterm);
		lterm=new JLabel();
		lterm.setSize(100,30);
		lterm.setText("期限：");
		lterm.setLocation(80,50);;
		frame.add(lterm);
		
		tnumbers=new JTextField();
		tnumbers.setSize(200,30);
		tnumbers.setLocation(180,80);
		frame.add(tnumbers);
		lnumbers=new JLabel();
		lnumbers.setSize(100,30);
		lnumbers.setText("册数：");
		lnumbers.setLocation(80,80);;
		frame.add(lnumbers);
		
		trenew=new JTextField();
		trenew.setSize(200,30);
		trenew.setLocation(180,110);
		frame.add(trenew);
		lrenew=new JLabel();
		lrenew.setSize(100,30);
		lrenew.setText("续借：");
		lrenew.setLocation(80,110);;
		frame.add(lrenew);
		
		tfine=new JTextField();
		tfine.setSize(200,30);
		tfine.setLocation(180,140);
		frame.add(tfine);
		lfine=new JLabel();
		lfine.setSize(100,30);
		lfine.setText("罚款：");
		lfine.setLocation(80,140);;
		frame.add(lfine);
			
		frame.setVisible(true);
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		JButton source=(JButton)e.getSource();
		if(source.getText().toString().equals("修改"))
		{	int term=Integer.parseInt(tterm.getText().toString());
			int numbers=Integer.parseInt(tnumbers.getText().toString());
			int renew=Integer.parseInt(tterm.getText().toString());
			int fine=Integer.parseInt(tfine.getText().toString());
			String str="UPDATE RULE SET TERM="+ term+",NUMBERS="
			+ numbers+",RENEW="+ renew+",FINE="+ fine+" WHERE CTYPENO="
			+ ctypeno+" and RTYPENO="+ rtypeno;
			try {
				Class.forName("oracle.jdbc.driver.OracleDriver").newInstance();
				String url="jdbc:oracle:thin:@localhost:1521:orcl";
				conn= DriverManager.getConnection(url,"system","admin");
				st=conn.createStatement();
				st.execute(str);
				JOptionPane.showMessageDialog(frame,"修改成功");
				conn.close();
			}catch (Exception e1) {
					e1.printStackTrace();
				}
		}
		else
		{
			System.exit(0);
		}
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

}
