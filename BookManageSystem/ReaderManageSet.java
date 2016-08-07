import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;
public class ReaderManageSet implements MouseListener{
	public JFrame frame;
	public JTextField trtypeno;
	public JLabel lrtypeno;
	public JTextField tpower;
	public JLabel lpower;
	public JButton set;
	public JButton exit_;
	public Connection conn;
	public Statement st;
	public static int rno;
	public ReaderManageSet(int rno)
	{	this.rno=rno;
		frame=new JFrame();
		frame.setSize(500,350);
		frame.setTitle("Login/Manage/ReaderMange/Set");
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
		
		trtypeno=new JTextField();
		trtypeno.setSize(200,30);
		trtypeno.setLocation(180,100);
		frame.add(trtypeno);
		lrtypeno=new JLabel();
		lrtypeno.setSize(100,30);
		lrtypeno.setText("新读者类型号：");
		lrtypeno.setLocation(80,100);;
		frame.add(lrtypeno);
		
		tpower=new JTextField();
		tpower.setSize(200,30);
		tpower.setLocation(180,150);
		frame.add(tpower);
		lpower=new JLabel();
		lpower.setSize(100,30);
		lpower.setText("新权限：");
		lpower.setLocation(80,150);;
		frame.add(lpower);
			
		frame.setVisible(true);
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		JButton source=(JButton)e.getSource();
		if(source.getText().toString().equals("修改"))
		{	int rtypeno=Integer.parseInt(trtypeno.getText().toString());
			int power=Integer.parseInt(tpower.getText().toString());
			String str="UPDATE READER SET RTYPENO="+ rtypeno+",POWER="+ power
					+" where RNO="+ rno;
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
