import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;
public class RuleManageAdd implements MouseListener{
	public JFrame frame;
	public JTextField tctypeno;
	public JLabel lctypeno;
	public JTextField trtypeno;
	public JLabel lrtypeno;
	public JTextField tterm;
	public JLabel lterm;
	public JTextField tnumbers;
	public JLabel lnumbers;
	public JTextField trenew;
	public JLabel lrenew;
	public JTextField tfine;
	public JLabel lfine;
	
	public JButton add;
	public JButton exit_;
	
	public Connection conn;
	public Statement st;
	public RuleManageAdd()
	{	frame=new JFrame();
		frame.setSize(500,350);
		frame.setTitle("Login/Manage/RuleManage/Add");
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
		
		tctypeno=new JTextField();
		tctypeno.setSize(200,30);
		tctypeno.setLocation(180,30);
		frame.add(tctypeno);
		lctypeno=new JLabel();
		lctypeno.setSize(100,30);
		lctypeno.setText("藏书类型：");
		lctypeno.setLocation(80,30);;
		frame.add(lctypeno);
		
		trtypeno=new JTextField();
		trtypeno.setSize(200,30);
		trtypeno.setLocation(180,60);
		frame.add(trtypeno);
		lrtypeno=new JLabel();
		lrtypeno.setSize(100,30);
		lrtypeno.setText("读者类型：");
		lrtypeno.setLocation(80,60);;
		frame.add(lrtypeno);
		
		tterm=new JTextField();
		tterm.setSize(200,30);
		tterm.setLocation(180,90);
		frame.add(tterm);
		lterm=new JLabel();
		lterm.setSize(100,30);
		lterm.setText("期限（天）：");
		lterm.setLocation(80,90);;
		frame.add(lterm);
		
		tnumbers=new JTextField();
		tnumbers.setSize(200,30);
		tnumbers.setLocation(180,120);
		frame.add(tnumbers);
		lnumbers=new JLabel();
		lnumbers.setSize(100,30);
		lnumbers.setText("册数：");
		lnumbers.setLocation(80,120);;
		frame.add(lnumbers);
		
		trenew=new JTextField();
		trenew.setSize(200,30);
		trenew.setLocation(180,150);
		frame.add(trenew);
		lrenew=new JLabel();
		lrenew.setSize(100,30);
		lrenew.setText("续借天数：");
		lrenew.setLocation(80,150);;
		frame.add(lrenew);
		
		tfine=new JTextField();
		tfine.setSize(200,30);
		tfine.setLocation(180,180);
		frame.add(tfine);
		lfine=new JLabel();
		lfine.setSize(100,30);
		lfine.setText("罚款：");
		lfine.setLocation(80,180);;
		frame.add(lfine);
		
		
		frame.setVisible(true);	
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		JButton source=(JButton)e.getSource();
		if(source.getText().toString().equals("添加"))
		{	int CTYPENO=Integer.parseInt(tctypeno.getText().toString());
			int RTYPENO=Integer.parseInt(trtypeno.getText().toString());
			int TERM=Integer.parseInt(tterm.getText().toString());
			int NUMBERS=Integer.parseInt(tnumbers.getText().toString());
			int RENEW=Integer.parseInt(trenew.getText().toString());
			int FINE=Integer.parseInt(tfine.getText().toString());
			String str="insert into RULER VALUES("+ CTYPENO+","
					+ RTYPENO+","+ TERM+","+ NUMBERS+","+ RENEW+","+ FINE+")";
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
