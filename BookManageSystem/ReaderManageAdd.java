import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;
public class ReaderManageAdd implements MouseListener{
	public JFrame frame;
	public JTextField trname;
	public JLabel lrname;
	public JTextField tphone;
	public JLabel lphone;
	public JTextField tmail;
	public JLabel lmail;
	public JTextField tdept;
	public JLabel ldept;
	public JTextField tpower;
	public JLabel lpower;
	public JTextField trtypeno;
	public JLabel lrtypeno;
	public JTextField trmarks;
	public JLabel lrmarks;
	public JButton add;
	public JButton exit_;
	public Connection conn;
	public Statement st;
	public ReaderManageAdd()
	{	frame=new JFrame();
		frame.setSize(500,350);
		frame.setTitle("Login/Manage/ReaderMange/Add");
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
		
		trname=new JTextField();
		trname.setSize(200,30);
		trname.setLocation(180,30);
		frame.add(trname);
		lrname=new JLabel();
		lrname.setSize(100,30);
		lrname.setText("姓名：");
		lrname.setLocation(80,30);;
		frame.add(lrname);
		
		tphone=new JTextField();
		tphone.setSize(200,30);
		tphone.setLocation(180,60);
		frame.add(tphone);
		lphone=new JLabel();
		lphone.setSize(100,30);
		lphone.setText("电话：");
		lphone.setLocation(80,60);;
		frame.add(lphone);
		
		tmail=new JTextField();
		tmail.setSize(200,30);
		tmail.setLocation(180,90);
		frame.add(tmail);
		lmail=new JLabel();
		lmail.setSize(100,30);
		lmail.setText("e-mail：");
		lmail.setLocation(80,90);;
		frame.add(lmail);
		
		tdept=new JTextField();
		tdept.setSize(200,30);
		tdept.setLocation(180,120);
		frame.add(tdept);
		ldept=new JLabel();
		ldept.setSize(100,30);
		ldept.setText("系：");
		ldept.setLocation(80,120);;
		frame.add(ldept);
		
		tpower=new JTextField();
		tpower.setSize(200,30);
		tpower.setLocation(180,150);
		frame.add(tpower);
		lpower=new JLabel();
		lpower.setSize(100,30);
		lpower.setText("权限：");
		lpower.setLocation(80,150);;
		frame.add(lpower);
		
		trtypeno=new JTextField();
		trtypeno.setSize(200,30);
		trtypeno.setLocation(180,180);
		frame.add(trtypeno);
		lrtypeno=new JLabel();
		lrtypeno.setSize(100,30);
		lrtypeno.setText("读者类型号：");
		lrtypeno.setLocation(80,180);;
		frame.add(lrtypeno);
		
		trmarks=new JTextField();
		trmarks.setSize(200,30);
		trmarks.setLocation(180,210);
		frame.add(trmarks);
		lrmarks=new JLabel();
		lrmarks.setSize(100,30);
		lrmarks.setText("备注：");
		lrmarks.setLocation(80,210);;
		frame.add(lrmarks);
		
		frame.setVisible(true);
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		JButton source=(JButton)e.getSource();
		if(source.getText().toString().equals("添加"))
		{
			String str="insert into READER VALUES(SEQ_RNO.NEXTVAL,'"+ trname.getText().toString()+"','"
+ tphone.getText().toString()+"','"+ tmail.getText().toString()+"','"+ tdept.getText().toString()+"',"
+ tpower.getText().toString()+","+ trtypeno.getText().toString()+",'"+ trmarks.getText().toString()+"')";
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
