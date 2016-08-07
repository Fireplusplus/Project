import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;

public class RuleManage implements MouseListener{
	public JFrame frame;
	public JButton select;
	public JButton add;
	public JButton set;
	public JButton delete;
	public JButton exit_;
	public JTextField tctypeno;
	public JLabel lctypeno;
	public JTextField trtypeno;
	public JLabel lrtypeno;
	public Connection conn;
	public Statement st;
	public static int ctypeno;
	public static int rtypeno;
	public RuleManage()
	{	frame=new JFrame();
		frame.setSize(500,350);
		frame.setTitle("Login/Manage/RuleManage");
		frame.setLayout(null);
		select=new JButton();
		add=new JButton();
		set=new JButton();
		delete=new JButton();
		exit_=new JButton();
		tctypeno=new JTextField();
		lctypeno=new JLabel();
		trtypeno=new JTextField();
		lrtypeno=new JLabel();
		
		exit_.setSize(60,30);
		exit_.setLocation(5,275);
		exit_.setText("退出");
		frame.add(exit_);
		exit_.addMouseListener(this);
		
		lctypeno.setSize(100,30);
		lctypeno.setLocation(80,20);
		lctypeno.setText("藏书类型编号：");
		frame.add(lctypeno);
		tctypeno.setSize(200,30);
		tctypeno.setLocation(180,20);
		frame.add(tctypeno);
		
		lrtypeno.setSize(100,30);
		lrtypeno.setLocation(80,50);
		lrtypeno.setText("读者类型编号：");
		frame.add(lrtypeno);
		trtypeno.setSize(200,30);
		trtypeno.setLocation(180,50);
		frame.add(trtypeno);
		
		select.setSize(200,50);
		select.setLocation(180,80);
		select.setText("查询");
		select.addMouseListener(this);
		frame.add(select);
		
		add.setSize(200,50);
		add.setLocation(180,130);
		add.setText("添加");
		frame.add(add);
		add.addMouseListener(this);
		
		set.setSize(200,50);
		set.setLocation(180,180);
		set.setText("修改");
		set.addMouseListener(this);
		frame.add(set);
		
		delete.setSize(200,50);
		delete.setLocation(180,230);
		delete.setText("删除");
		delete.addMouseListener(this);
		frame.add(delete);
		
		frame.setVisible(true);
	}
	@Override
	public void mouseClicked(MouseEvent e) {
		JButton source=(JButton)e.getSource();
		int CTYPENO=Integer.parseInt(tctypeno.getText().toString());
		int RTYPENO=Integer.parseInt(trtypeno.getText().toString());
		ctypeno=CTYPENO;
		rtypeno=RTYPENO;
		if(source.getText().toString().equals("查询"))
		{	try {
			Class.forName("oracle.jdbc.driver.OracleDriver").newInstance();
			String url="jdbc:oracle:thin:@localhost:1521:orcl";
			conn= DriverManager.getConnection(url,"system","admin");
			st=conn.createStatement();
			String sel="select * from RULE WHERE CTYPENO="
			+ CTYPENO+" AND RTYPENO="+ RTYPENO;
			ResultSet re=st.executeQuery(sel);
			if(re.next())
			{
				StringBuffer str=new StringBuffer();
				for(int i=0;i<6;i++)
				{
					str.append(re.getString(i+1));
					str.append(" ");
				}
				JOptionPane.showMessageDialog(frame,str);
			}
			else
				JOptionPane.showMessageDialog(frame,"查无此规则");
			conn.close();
			} 
			catch (Exception e1) {
				e1.printStackTrace();
			}
			
		}
		else if(source.getText().toString().equals("添加"))
		{
			RuleManageAdd r=new RuleManageAdd();
		}
		else if(source.getText().toString().equals("修改"))
		{
			RuleManageSet r1=new RuleManageSet(ctypeno,rtypeno);
		}
		else if(source.getText().toString().equals("删除"))
		{	try {
			Class.forName("oracle.jdbc.driver.OracleDriver").newInstance();
			String url="jdbc:oracle:thin:@localhost:1521:orcl";
			conn= DriverManager.getConnection(url,"system","admin");
			st=conn.createStatement();
			String remove="DELETE FROM RULE WHERE CTYPENO="
					+ CTYPENO+" AND RTYPENO="+ RTYPENO;
			st.execute(remove);
			JOptionPane.showMessageDialog(frame,"删除成功");
			conn.close();
			} 
			catch (Exception e1) {
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
