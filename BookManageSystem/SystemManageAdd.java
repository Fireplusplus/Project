import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;
public class SystemManageAdd implements MouseListener{
	public JFrame frame;
	public JTextField taccount;
	public JLabel laccount;
	public JTextField tkey;
	public JLabel lkey;
	public JButton add;
	public JButton exit_;
	public Connection conn;
	public Statement st;
	
	public SystemManageAdd()
	{	frame=new JFrame();
		frame.setSize(500,350);
		frame.setTitle("Login/Manage/SystemManage/Add");
		frame.setLayout(null);
		
		add=new JButton();
		add.setSize(60,30);
		add.setText("添加");
		add.setLocation(100,250);
		frame.add(add);
		add.addMouseListener(this);
		exit_=new JButton();
		exit_.setSize(60,30);
		exit_.setText("退出");
		exit_.setLocation(280,250);
		frame.add(exit_);
		exit_.addMouseListener(this);
		
		taccount=new JTextField();
		taccount.setSize(200,30);
		taccount.setLocation(180,50);
		frame.add(taccount);
		laccount=new JLabel();
		laccount.setSize(100,30);
		laccount.setText("新账号：");
		laccount.setLocation(80,50);;
		frame.add(laccount);
		
		tkey=new JTextField();
		tkey.setSize(200,30);
		tkey.setLocation(180,100);
		frame.add(tkey);
		lkey=new JLabel();
		lkey.setSize(100,30);
		lkey.setText("新密码：");
		lkey.setLocation(80,100);;
		frame.add(lkey);
	
		
		frame.setVisible(true);
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		JButton source=(JButton)e.getSource();
		if(source.getText().toString().equals("添加"))
		{	String account=taccount.getText().toString();
			String key=tkey.getText().toString();
			String str="INSERT INTO ADMIN VALUES(SEQ_ANO.NEXTVAL,'"
					+ account+"','"+ key+"')";
			try {
				Class.forName("oracle.jdbc.driver.OracleDriver").newInstance();
				String url="jdbc:oracle:thin:@localhost:1521:orcl";
				conn= DriverManager.getConnection(url,"system","admin");
				st=conn.createStatement();
				st.execute(str);
				JOptionPane.showMessageDialog(frame,"添加成功");
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
